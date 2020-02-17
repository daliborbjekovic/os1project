/*
 * PCB.cpp
 *
 *  Created on: Jul 25, 2018
 *      Author: OS1
 */
#include "PCB.h"
#include "lock.h"
#include "List.h"
#include "dos.h"
#include "SCHEDULE.h"



volatile PCB * PCB::running = 0;

extern List <PCB*> sleepingThreads;

void PCB::wrapper() // moraces da promenis kada odg nit budes cuvao na steku
{
	PCB::running->myThread->run();
	lock
	((PCB*)PCB::running)->waitingForMeToEnd.signalAll();
	PCB::running->zavrsio=1;
	unlock
	dispatch();
}

unsigned int PCB::getKvant()
{
	return PCB::running->kvant;
}

PCB::PCB (unsigned long stackSize,unsigned int timeSlice,Thread* myT):myThread(myT),waitingForMeToEnd(0)
{

	if(stackSize<=4096)this->stackSize=stackSize;
	else this->stackSize=4096;
	kvant=timeSlice;
	stack= new unsigned[this->stackSize];

	stack[stackSize-1]=0x200; //-3
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-2]= FP_SEG(wrapper);//-4
	stack[stackSize-3]= FP_OFF(wrapper);//-5
	ss= FP_SEG(&stack[stackSize-12]); // bice -14 kad ubacis adresu odg niti na stek umesto myThread
	sp= FP_OFF(&stack[stackSize-12]);
#endif

	zavrsio=0;blocked=0;sleeping=0;started=0;
}

void PCB::waitToComplete()
{
	//if(zavrsio==0)waitingForMeToEnd.wait(1);
	while(zavrsio==0)dispatch();
}

void PCB::sleep(unsigned int timeToSleep)
{
	lock
	PCB::running->sleeping=1;
    PCB::running->timeForSleepLeft=timeToSleep;
    sleepingThreads.add((PCB*)PCB::running);
	unlock
    dispatch();
}

void PCB::start()
{
	if(started==0)
	{
	Scheduler::put(this);
	started=1;
	}
}
