/*
 * kernevt.h
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#ifndef KERNEVT_H_
#define KERNEVT_H_

#include "event.h"
#include "PCB.h"
#include "IVTEntry.h"

class KernelEv
{
private:
	IVTEntry * myIvtEntry;
	PCB* OwnerThreadPCB;
	Semaphore* eventSem;

	static void SignalEve(Event* e) {e->signal();}

public:
	friend class IVTEntry;

	KernelEv(IVTNo ivtNo,Event * e);
	~KernelEv();

	void wait();
	void signal();
};

#endif /* KERNEVT_H_ */
