/*
 * kernevt.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#include "kernevt.h"
#include "semaphor.h"
#include "PCB.h"

KernelEv::KernelEv(IVTNo ivtNo, Event* e)
{
	myIvtEntry = IVTEntry::getEntryAt(ivtNo);
	myIvtEntry->setMyEvent(e);
	myIvtEntry->setIVector();
	eventSem= new Semaphore(0);
	OwnerThreadPCB=(PCB*)PCB::running;
}

KernelEv::~KernelEv()
{
	delete eventSem;

}

void KernelEv::signal()
{
	eventSem->signal();
}

void KernelEv::wait()
{
	if((PCB*)PCB::running==OwnerThreadPCB)eventSem->wait(1);
}

