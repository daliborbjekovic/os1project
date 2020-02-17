/*
 * IVTEntry.cpp
 *
 *  Created on: Dec 22, 2018
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "kernevt.h"

IVTEntry ** IVTEntry::EntryTable= new IVTEntry*[256];

IVTEntry::IVTEntry(unsigned char ivtNo,pInterrupt newRoutine)
{
	IVTEntry::EntryTable[ivtNo]=this;
	EntryNumber=ivtNo;
	NewRoutine=newRoutine;
	OldRoutine=0;
	myEvent=0;
#ifndef BCC_BLOCK_IGNORE
	asm cli
	OldRoutine= getvect(ivtNo);
	asm sti
#endif
}

IVTEntry::~IVTEntry()
{
	IVTEntry::EntryTable[EntryNumber]=0;
#ifndef BCC_BLOCK_IGNORE
	asm cli
	setvect(EntryNumber,OldRoutine);
	asm sti
#endif
}

void IVTEntry::SignalWrapper()
{
	KernelEv::SignalEve(myEvent);
}

void IVTEntry::setIVector()
{
#ifndef BCC_BLOCK_IGNORE
	asm cli
	setvect(EntryNumber,NewRoutine);
	asm sti
#endif
}
