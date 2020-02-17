/*
 * thread.cpp
 *
 *  Created on: Nov 11, 2018
 *      Author: OS1
 */
#include "thread.h"
#include "dos.h"
#include "PCB.h"
#include "timer.h"
#include "lock.h"



Thread::Thread (StackSize stackSize, Time timeSlice)
{
	myPCB= new PCB(stackSize,timeSlice,this);
}

Thread::~Thread() // privremena metoda
{

	delete myPCB;
}

void Thread::start()
{
		myPCB->start();
}

void Thread::waitToComplete()
{
	if(myPCB)myPCB->waitToComplete(); // menjacu kad budem napravio dogadjaje ili semafore;
}

 void Thread::sleep(Time timeToSleep)
{
	 PCB::sleep(timeToSleep);
}

unsigned tsp,tss;

volatile int zahtevana_promena_konteksta=0;
volatile int brojac=0;

void dispatch() // Moraces da sklonis interrupt kada implementiras timer()
{
#ifndef BCC_BLOCK_IGNORE // promenices kad i lock()
	asm cli
#endif
	zahtevana_promena_konteksta=1;
	timer();
#ifndef BCC_BLOCK_IGNORE // promenices kad i unlock()
	asm sti
#endif
}




