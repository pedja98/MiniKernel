/*
 * KerEv.h
 *
 *  Created on: Aug 28, 2020
 *      Author: OS1
 */

#ifndef KEREV_H_
#define KEREV_H_

#include "pcb.h"
#include "IvtEntry.h"

class KernelEv{

private:
	IVTEntry *entry;
	ID vlasnik;

public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void signal();
	void wait();
};


#endif /* KEREV_H_ */
