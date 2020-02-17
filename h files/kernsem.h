/*
 * kernsem.h
 *
 *  Created on: Aug 1, 2018
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include "semaphor.h"
#include "List.h"

class PCB;

class KernelSem
{
private:
	friend class Semaphore;
	friend class PCB;


	KernelSem(int init)
	{
		value=init;
	}

	int value;

	List <PCB *> blockedBySem;

	int wait(int toBlock);

	void signal();

	void signalAll();
};



#endif /* KERNSEM_H_ */
