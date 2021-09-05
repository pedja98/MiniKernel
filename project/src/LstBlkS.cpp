/*
 * LstBlkS.cpp
 *
 *  Created on: Aug 18, 2020
 *      Author: OS1
 */

#include "LstBlkS.h"
#include "KerSem.h"
#include "funk.h"

extern volatile int brBlokiranih;

LstBlkS::LstBlkS(KernalSem *i){
	this->s=i;
	this->id=s->getId();
	this->prvi=0;
	this->posl=0;
	this->br=0;
}

LstBlkS::~LstBlkS(){
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

void LstBlkS::dodaj(PCB *p){
	lock();
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
	unlock();
}

ID LstBlkS::getId() const{
	return this->id;
}

int LstBlkS::isprSaVrha(int i){
    lock();
	int j=0;
	while(this->prvi!=0 && j<i){
		this->prvi->pcb->setBlkNeo(1);
		Elem *p=prvi;
		if(p==0){
			continue;
		}
		prvi=prvi->sled;
		p->sled=0;
		j++;
		brBlokiranih--;
		this->br--;
		p->pcb->setBlock(0);
		Scheduler::put(p->pcb);
		p->pcb->setOdblkSig(1);
		delete p;
	}
	this->s->dodaj(i);
	unlock();
	return j;
}

void LstBlkS::obrElById(ID id){
	Elem *tek=this->prvi;
	Elem *pret=0;
	while(tek){
		if(tek->pcb->getId()==id){
	     	break;
		}
		pret=tek;
		tek=tek->sled;
	}
	if(tek!=0){
		this->br--;
		brBlokiranih--;
		tek->pcb->setBlock(0);
		Scheduler::put(tek->pcb);
		if(pret==0){
		   if(tek->sled==0){
			  prvi=0;
			  posl=0;
			  delete tek;
		   }
		   else{
				prvi=tek->sled;
				delete tek;
		   }
		}
		else{
	     	if(tek->sled==0){
		    	posl=pret;
			    posl->sled=0;
				delete tek;
			}
			else{
				pret->sled=tek->sled;
				tek->sled=0;
				delete tek;
			}
		}
	}
	if(this->br==0){
		this->prvi=0;
		this->posl=0;
	}
}

void LstBlkS::prolaz(){
	lock();
	Elem *tek=this->prvi;
	while(tek!=0){
		Elem *p=tek;
		if(p->pcb->getBlkNeo()==0){
			Time t=p->pcb->getVrBlk();
			t--;
			p->pcb->setVrBlk(t);
		}
		tek=tek->sled;
	}

	tek=this->prvi;

	while(tek!=0){
		Elem *p=tek;
		tek=tek->sled;
		if(p->pcb->getVrBlk()==0 && p->pcb->getBlkNeo()==0){
			lock();
			p->pcb->setOdblkSig(0);
			this->s->dodaj(1);
			this->obrElById(p->pcb->getId());
			unlock();
		}
	}
	unlock();
}
