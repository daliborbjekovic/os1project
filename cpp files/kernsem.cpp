/*
 * kernsem.cpp
 *
 *  Created on: Aug 1, 2018
 *      Author: OS1
 */

#include "PCB.h"
#include "kernsem.h"
#include "lock.h"
#include "SCHEDULE.H"

int KernelSem::wait (int toBlock)
{
	lock
	if(toBlock==0)
		{
			if(value>0)
			{
				value-=1;
				unlock
				return 0;
			}
			else
			{
				unlock
				return -1;
			}
		}
		else
		{
			if(--value<0)
			{
				PCB::running->blocked=1;
				blockedBySem.add((PCB*)PCB::running);
				unlock
				dispatch();
				return 1;
			}
			else
			{
				unlock
				return 0;
			}
		}
}

void KernelSem::signal()
{
	lock
	if(++value<=0)
	{
		PCB * unblocked=blockedBySem.remove();
		unblocked->blocked=0;
		Scheduler::put(unblocked);
	}
	unlock
}

void KernelSem::signalAll()
{
	while(value<0)signal();
}
