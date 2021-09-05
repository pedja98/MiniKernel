/*
 * KerSem.h
 *
 *  Created on: Aug 17, 2020
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "semaphor.h"
#include "funk.h"
#include "LstBlkS.h"
#include "LstSem.h"

class KernalSem{

private:
	int val;
	int id;
	static int Iden;
	Semaphore *mySem;

public:
	static volatile LstSem *lS;
	volatile LstBlkS *lbs;
	KernalSem(Semaphore *s,int init);
	~KernalSem();
	int getId() const;
	int getVal() const;
	Semaphore* getMySem() const;
	int wait(Time time);
	int signal(int n);
	void dodaj(int i);
	void oduzmi(int i);
};
#endif /* KERSEM_H_ */
