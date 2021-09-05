/*
 * LstBlk.h
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#ifndef LSTBLK_H_
#define LSTBLK_H_

#include "thread.h"

class LstBlk{

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
	ID id;

public:
	LstBlk();
	~LstBlk();
	void dodaj(PCB *p);
	void isprLst();

	void setID(ID i);

};
#endif /* LSTBLK_H_ */
