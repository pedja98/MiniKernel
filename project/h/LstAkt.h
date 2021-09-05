/*
 * LstAkt.h
 *
 *  Created on: Jul 29, 2020
 *      Author: OS1
 */

#ifndef LSTAKT_H_
#define LSTAKT_H_

#include "thread.h"

class LstAkt{

private:
	struct Elem{
		PCB *pcb;
		Elem *sled;
		Elem(PCB *p){
			pcb=p;
			sled=0;
		}
	};
	Elem *prvi, *posl;
	int br;

public:
	LstAkt();
	~LstAkt();
	void dodaj(PCB *p);
	PCB* getElById(ID id);
	void obrElById(ID id);
	void mainWaitAll();
};

#endif /* LSTAKT_H_ */
