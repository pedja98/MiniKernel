/*
 * LstAkt.cpp
 *
 *  Created on: Jul 29, 2020
 *      Author: OS1
 */

#include "LstAkt.h"
#include "pcb.h"
#include "funk.h"

extern volatile PCB* pcbIt;
extern volatile PCB *pcbMain;

LstAkt::LstAkt(){
   this->br=0;
   this->prvi=0;
   this->posl=0;
}

LstAkt::~LstAkt(){
	Elem *tek = this->prvi;
	while(tek){
		Elem *p=tek;
		tek=tek->sled;
        lock();
        this->br--;
		delete p;
		unlock();
	}
	this->prvi=0;
	this->posl=0;
}

void LstAkt::obrElById(ID id){
    lock();
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
	unlock();
}

void LstAkt::dodaj(PCB *p){
	this->br++;
	if(this->prvi==0){
		this->prvi=new Elem(p);
		this->posl=this->prvi;
	}
	else{

		this->posl->sled=new Elem(p);
		this->posl=this->posl->sled;
	}
}

PCB* LstAkt::getElById(ID id){
	Elem *tek=this->prvi;
	while(tek){
		if(tek->pcb->getId()==id){
			return tek->pcb;
		}
		tek=tek->sled;
	}
	return 0;
}

void LstAkt::mainWaitAll(){
     if(((PCB*)PCB::running)->getStart()!=2){
		return;
	 }
     Elem *tek=this->prvi;
     while(tek!=0){
    	 if(tek->pcb->getId()!=((PCB*)pcbIt)->getId() && tek->pcb->getId()!=((PCB*)pcbMain)->getId() ){
    		tek->pcb->waitToCmp();
    	 }
    	 tek=tek->sled;
     }
}
