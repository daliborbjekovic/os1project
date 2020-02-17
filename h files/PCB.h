/*
 * PCB.h
 *
 *  Created on: Jul 25, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
#include "kernsem.h"

class PCB
{
private:
	friend class Thread;
	friend class KernelSem;

	friend void dispatch();
	friend void interrupt timer();

	 unsigned * stack;
	 unsigned long stackSize;

	 unsigned sp;
	 unsigned ss;

	 unsigned int kvant; // moraces da implementiras beskonacnu nit sa timeslice=0
	 unsigned int timeForSleepLeft;

	 int id; // moraces kasnije da implementiras id dodelu

	 Thread* myThread; // moraces da cuvas adresu odgovarajuce niti na steku
	 KernelSem waitingForMeToEnd;

	 static void wrapper(); // moraces da promenis kada odg nit budes cuvao na steku



	 unsigned zavrsio,blocked,sleeping,started; // koristices kada budes implementirao destruktor i waittocomplete()


	 PCB (unsigned long stackSize,unsigned int timeSlice,Thread* myT);

	 void waitToComplete();

	 static void sleep(unsigned int timeToSleep);

	 void start();

	 ~PCB() {delete [] stack;}

public:
	 static volatile  PCB * running;

	 PCB():waitingForMeToEnd(0),ss(0),sp(0),kvant(2),zavrsio(0),started(0),id(0),timeForSleepLeft(0),myThread(0),blocked(0),sleeping(0),stackSize(0),stack(0){}

	static unsigned int getKvant();
};


#endif /* PCB_H_ */
