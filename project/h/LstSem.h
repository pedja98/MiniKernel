/*
 * LstSem.h
 *
 *  Created on: Aug 18, 2020
 *      Author: OS1
 */

#ifndef LSTSEM_H_
#define LSTSEM_H_

#include"semaphor.h"
#include "thread.h"

class LstSem{

private:
	struct Elem{
		KernalSem *ks;
		Elem *sled;
		Elem(KernalSem *p){
			ks=p;
			sled=0;
		}
	};
	Elem *prvi, *posl;
	int br;

public:
	LstSem();
	~LstSem();
	void dodaj(KernalSem *p);
	void obrElById(ID id);
	void prolaz();
};
#endif /* LSTSEM_H_ */
