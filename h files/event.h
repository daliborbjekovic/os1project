/*
 * event.h
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

typedef unsigned char IVTNo;

#include "IVTEntry.h"
#include "dos.h"

#define PREPAREENTRY(ivtNo, callold) void interrupt routine##ivtNo##(...) \
{\
	IVTEntry::getEntryAt(##ivtNo##)->SignalWrapper(); \
	if(##callold##) \
	{\
		IVTEntry::getEntryAt(##ivtNo##)->callOldRoutine();\
	}\
}\
	IVTEntry entry##ivtNo##(##ivtNo##,routine##ivtNo##);





class KernelEv;

class Event {
public:

 Event (IVTNo ivtNo);
 ~Event ();

 void wait ();

protected:

 friend class KernelEv;
 void signal(); // can call KernelEv

private:
 KernelEv* myImpl;

};


#endif /* EVENT_H_ */
