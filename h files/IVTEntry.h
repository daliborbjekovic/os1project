/*
 * IVTEntry.h
 *
 *  Created on: Dec 22, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "dos.h"
#include "semaphor.h"

typedef void interrupt (*pInterrupt)(...);

class Event;

class IVTEntry{
public:
	IVTEntry(unsigned char ivtNo,pInterrupt newRoutine);
	~IVTEntry();

	static IVTEntry * getEntryAt(unsigned char ivtNo){return EntryTable[ivtNo];}

	Event * getMyEvent() {return myEvent;}

	void setMyEvent( Event* e) {myEvent=e;}

	void setNewRoutine(pInterrupt newRoutine) {NewRoutine=newRoutine;}

	void setIVector();

	void callOldRoutine() {OldRoutine();}

	void SignalWrapper();


private:
	unsigned char EntryNumber;
	static IVTEntry ** EntryTable;
	Event * myEvent;
	pInterrupt NewRoutine,OldRoutine;
};


#endif /* IVTENTRY_H_ */
