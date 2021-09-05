/*
 * LstBlk.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#include"LstBlk.h"
#include"pcb.h"
#include "funk.h"

extern volatile int brBlokiranih;

LstBlk::LstBlk(){
	this->id=0;
	this->prvi=0;
	this->posl=0;
	this->br=0;
}

LstBlk::~LstBlk(){
	Elem *tek=prvi;
	while(tek){
	  Elem *p=tek;
	  tek=tek->sled;
      lock();
      brBlokiranih--;
      this->br--;
	  delete p;
	  unlock();
	}
	this->posl=0;
	this->prvi=0;
}

void LstBlk::dodaj(PCB *p){
	this->br++;
	brBlokiranih++;
	if(this->prvi==0){
		this->prvi=new Elem(p);
		this->posl=this->prvi;
	}
	else{
		this->posl->sled=new Elem(p);
		this->posl=this->posl->sled;
	}
}

void LstBlk::isprLst(){
	Elem *tek=prvi;
	while(tek){
	  Elem *p=tek;
	  tek=tek->sled;
	  p->pcb->setBlock(0);
	  Scheduler::put(p->pcb);
	  brBlokiranih--;
	  delete p;
	}
	this->posl=0;
	this->prvi=0;
	this->br=0;
}

void LstBlk::setID(ID i){
	this->id=i;
}
