/*
 * LstSem.cpp
 *
 *  Created on: Aug 18, 2020
 *      Author: OS1
 */

#include "LstSem.h"
#include "KerSem.h"

LstSem::LstSem(){
    this->prvi=0;
    this->posl=0;
    this->br=0;
}

LstSem::~LstSem(){
	Elem *tek=prvi;
	while(tek){
	  Elem *p=tek;
	  tek=tek->sled;
	  lock();
	  this->br--;
	  delete p;
      unlock();
	}
	this->posl=0;
	this->prvi=0;
}

void LstSem::dodaj(KernalSem *p){
	lock();
	this->br++;
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

void LstSem::prolaz(){
	Elem *tek=this->prvi;
	while(tek!=0){
		((LstBlkS*)tek->ks->lbs)->prolaz();
		tek=tek->sled;
	}
}

void LstSem::obrElById(ID id){
    lock();
	Elem *tek=this->prvi;
	Elem *pret=0;
	while(tek){
		if(tek->ks->getId()==id){
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
