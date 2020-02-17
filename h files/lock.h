/*
 * lock.h
 *
 *  Created on: Aug 1, 2018
 *      Author: OS1
 */

#ifndef LOCK_H_
#define LOCK_H_

extern volatile int dozvPromenaKonteksta;

#define hlock asm cli
#define hunlock asm sti

#define lock dozvPromenaKonteksta=0;
#define unlock dozvPromenaKonteksta=1;

#endif /* LOCK_H_ */
