/*
 * semaphor.cpp
 *
 *  Created on: Aug 1, 2018
 *      Author: OS1
 */

#include "semaphor.h"

#include "kernsem.h"

int Semaphore::val () const
{
	return myImpl->value;
}

Semaphore::Semaphore (int init)
{
	myImpl= new KernelSem(init);
}

 int Semaphore::wait (int toBlock)
{
	return myImpl->wait(toBlock);
}

 void Semaphore::signal()
{
	 myImpl->signal();
}

 Semaphore::~Semaphore()
 {
	 delete myImpl;
 }
