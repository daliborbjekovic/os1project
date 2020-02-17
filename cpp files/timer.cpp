/*
 * timer.cpp
 *
 *  Created on: Sep 18, 2018
 *      Author: OS1
 */
#include "PCB.h"
#include "dos.h"
#include "SCHEDULE.H"
#include "List.h"

extern volatile int zahtevana_promena_konteksta;
extern volatile int brojac;
extern unsigned tsp,tss;
extern void tick();

extern List <PCB*> sleepingThreads;
PCB* curr;
unsigned int i;
volatile int dozvPromenaKonteksta=1;


void interrupt timer()
{
	if(zahtevana_promena_konteksta==0)
	{
		tick();
		if(brojac!=-1)brojac--;
		sleepingThreads.putIterratorOnFirstPlace();
				curr=0;
				i=0;
				while((curr=sleepingThreads.showThenNextIterrator())!=0)
				{
					curr->timeForSleepLeft-=1;
					if(curr->timeForSleepLeft==0)
					{
						curr->sleeping=0;
						sleepingThreads.removeAt(i--);
						Scheduler::put(curr);
					}
					i++;
				}

	}
	if((brojac==0 || zahtevana_promena_konteksta==1)&&dozvPromenaKonteksta==1)// promeni uslov da dozv prom kont dozvoljava dispatch()
	{
#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tsp,sp
			mov tss,ss
		}
#endif
		PCB::running->sp=tsp;
		PCB::running->ss=tss;

		if(PCB::running->zavrsio==0 && PCB::running->blocked==0 && PCB::running->sleeping==0 )Scheduler::put((PCB*)PCB::running);
		PCB::running=Scheduler::get();

		if(PCB::running->kvant==0)
		{
			brojac=-1;
		}
		else
		{
			brojac=PCB::running->kvant;
		}

		tsp=PCB::running->sp;
		tss=PCB::running->ss;
#ifndef BCC_BLOCK_IGNORE
		asm{
			mov sp,tsp
			mov ss,tss
		}
#endif


	}
	if(zahtevana_promena_konteksta==0)
	{
#ifndef BCC_BLOCK_IGNORE
		asm int 60h;
#endif
	}
	zahtevana_promena_konteksta=0;
}


unsigned oldTimerOFF,oldTimerSEG;

void inic()
{
#ifndef BCC_BLOCK_IGNORE
	asm{
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr es:0022h
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer	 //postavlja
		mov word ptr es:0020h, offset timer //novu rutinu

		mov ax, oldTimerSEG	 //	postavlja staru rutinu
		mov word ptr es:0182h, ax //; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
#endif
}

void restore()
{
#ifndef BCC_BLOCK_IGNORE
	asm{
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
#endif
}
