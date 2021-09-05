/*
 * funk.h
 *
 *  Created on: Aug 1, 2020
 *      Author: OS1
 */

#ifndef FUNK_H_
#define FUNK_H_

#include "pcb.h"
#include "idleT.h"
#include "KerSem.h"
#include "KerEv.h"
#include "IvtEntry.h"

void inic();
void restore();

void interrupt timer(...);
void lock();
void unlock();

#endif /* FUNK_H_ */
