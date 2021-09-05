/*
 * KerSem.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: OS1
 */

#include"KerSem.h"
#include"funk.h"

int KernalSem::Iden=0;

volatile LstSem * KernalSem::lS=0;

KernalSem::KernalSem(Semaphore *s, int init){
	this->id=++Iden;

	if(init<0){
		init=0;
	}

	this->val=init;
	this->mySem=s;

	lock();
	if(KernalSem::lS==0){
		KernalSem::lS=new LstSem();
	}

	this->lbs=new LstBlkS(this);
	((LstSem *)KernalSem::lS)->dodaj(this);
	unlock();
}

KernalSem::~KernalSem(){
	lock();
	((LstSem*)KernalSem::lS)->obrElById(this->id);
	delete this->lbs;
	unlock();
}

void KernalSem::dodaj(int i){
	this->val+=i;
}

void KernalSem::oduzmi(int i){
	this->val-=i;
}

int KernalSem::getId() const{
	return this->id;
}

int KernalSem::getVal() const{
	return this->val;
}

Semaphore* KernalSem::getMySem() const{
	return this->mySem;
}

int KernalSem::wait(Time time){
	lock();
	this->oduzmi(1);
	if(this->val<0){
		if(time==0){
			((PCB*)PCB::running)->setVrBlk(0);
			((PCB*)PCB::running)->setBlkNeo(1);
			((PCB*)PCB::running)->setBlock(1);
			((LstBlkS*)KernalSem::lbs)->dodaj(((PCB*)PCB::running));
			unlock();
			dispatch();
			return 1;
		}
		else{
			((PCB*)PCB::running)->setVrBlk(time);
			((PCB*)PCB::running)->setBlkNeo(0);
			((PCB*)PCB::running)->setBlock(1);
			((LstBlkS*)KernalSem::lbs)->dodaj(((PCB*)PCB::running));
			unlock();
			dispatch();
			return ((PCB*)PCB::running)->getOdblkSig();
		}
	}
	unlock();
	return 1;
}

int KernalSem::signal(int n){
	lock();
	if(n<0){
		unlock();
		return n;
	}
	if(n==0){
		((LstBlkS*)KernalSem::lbs)->isprSaVrha(1);
		unlock();
		return 0;
	}
	int m=((LstBlkS*)KernalSem::lbs)->isprSaVrha(n);
	unlock();
	return m;
}

