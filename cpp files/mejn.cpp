/*
 * mejn.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: OS1
 */
#include "PCB.h"

#include "timer.h"
#include "List.h"

#include "Empty.h"

extern int userMain(int argc,char* argv []);

extern volatile int brojac;


List <PCB*> sleepingThreads;

int main(int argc, char* argv[])
{

	inic();//ubaci praznu nit

	volatile PCB* mejn= new PCB();
	PCB::running=mejn;
	brojac=PCB::getKvant();

	EmptyThread * e= new EmptyThread();
	e->start();
	int ret= userMain(argc,argv);
	e->doInterrupt();
	restore();

	return ret;
}

