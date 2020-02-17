/*
 * event.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#include "event.h"
#include "kernevt.h"

Event::Event(IVTNo ivtNo)
{
	myImpl=0;
	myImpl= new KernelEv(ivtNo,this);
}

Event::~Event() {delete myImpl;}

void Event::wait(){myImpl->wait();}
void Event::signal(){myImpl->signal();}


