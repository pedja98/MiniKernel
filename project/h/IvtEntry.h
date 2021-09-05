/*
 * IvtEntry.h
 *
 *  Created on: Aug 28, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "event.h"
#include "pcb.h"
#include "semaphor.h"

typedef void interrupt (*pInterrupt)(...);

class IVTEntry{

private:
	Semaphore s;
	pInterrupt staraRutina;
	IVTNo brojUlaza;

public:
	static IVTEntry ** et;
	IVTEntry(IVTNo ivtNo, pInterrupt prekid);
	~IVTEntry();
	void signal();
	void wait();
	static IVTEntry* getEntry(IVTNo ivtNo);
	void pozoviStaru();

};

#define PREPAREENTRY(brojRutine, pozovi)\
	void interrupt rutina##brojRutine(...);\
    IVTEntry ivt##brojRutine(brojRutine, rutina##brojRutine);\
    void interrupt rutina##brojRutine(...){\
    	ivt##brojRutine.signal();\
    	if(pozovi==1){\
		   ivt##brojRutine.pozoviStaru();\
    	}\
    }

#endif /* IVTENTRY_H_ */
