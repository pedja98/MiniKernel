/*
 * LstBlkS.h
 *
 *  Created on: Aug 18, 2020
 *      Author: OS1
 */

#ifndef LSTBLKS_H_
#define LSTBLKS_H_

#include"semaphor.h"
#include "thread.h"

class LstBlkS{

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
	KernalSem *s;
	int br;
	ID id;
	void obrElById(ID id);

public:
	LstBlkS(KernalSem *i);
	~LstBlkS();
	void dodaj(PCB *p);
	ID getId() const;
    int isprSaVrha(int i);
    void prolaz();

};
#endif /* LSTBLKS_H_ */
