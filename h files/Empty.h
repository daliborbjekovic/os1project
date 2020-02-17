/*
 * Empty.h
 *
 *  Created on: Aug 30, 2018
 *      Author: OS1
 */

#ifndef EMPTY_H_
#define EMPTY_H_

#include "Thread.h"

class EmptyThread : public Thread

{
private:
	int interrupted;
public:
	void doInterrupt() {interrupted=1;}
protected:
	virtual void run()
	{
		while(interrupted!=1)dispatch();
	}

};



#endif /* EMPTY_H_ */
