/*
 * pcb.cpp
 *
 *  Created on: Jul 27, 2020
 *      Author: OS1
 */

#include"pcb.h"
#include "funk.h"

volatile LstAkt* PCB::lA=0;

int PCB::Iden=0;

volatile PCB* PCB::running=0;

volatile int PCB::brPCB=0;

PCB::PCB(Thread* t,StackSize stackSize, Time timeSlice, int st){
	lock();
	if(((LstAkt*)PCB::lA)==0){
		((LstAkt*)PCB::lA)=new LstAkt();
	}

	if(stackSize>65535){
		stackSize=defaultStackSize;
	}

	this->id=++Iden;
	this->myThread=t;
	this->vreme=timeSlice;
	this->start=st;
	this->kraj=0;
	this->neogr=0;
	this->blocked=0;
	this->blkNeo=0;
	this->vrBlk=0;
	this->odblkSig=0;
	this->lB=new LstBlk();
	((LstBlk*)(this->lB))->setID(this->id);

	if(timeSlice==0){
		this->neogr=1;
	}

	if(this->start!=2){
       unsigned num=stackSize/sizeof(unsigned);
	   this->stek=new unsigned [num];

    #ifndef BCC_BLOCK_IGNORE
	   this->stek[num-1]=0x200;
	   this->stek[num-2] = FP_SEG(&(PCB::wrapper));
       this->stek[num-3] = FP_OFF(&(PCB::wrapper));
       this->sp=FP_OFF(this->stek+(num-12));
       this->ss=FP_SEG(this->stek+(num-12));
       this->bp=FP_OFF(this->stek+(num-12));
    #endif
    }

	else{
		this->stek=0;
		this->ss=0;
		this->sp=0;
		this->bp=0;
	}

	PCB::brPCB++;
	((LstAkt*)PCB::lA)->dodaj(this);

	unlock();
}

PCB::~PCB(){
	lock();
	delete this->lB;
	((LstAkt*)(PCB::lA))->obrElById(this->id);
	if(this->start!=2){
	  delete[] this->stek;
	}
	unlock();
}

Thread* PCB::getThr() const{
	return this->myThread;
}

void PCB::wrapper(){
	PCB::running->myThread->run();
	lock();
	((PCB*)PCB::running)->setKraj(1);
	((LstBlk*)((PCB*)PCB::running)->lB)->isprLst();
	PCB::brPCB--;
	unlock();
	dispatch();
}

int PCB::getId() const {
	return this->id;
}

int PCB::getStart() const{
   return this->start;
}

int PCB::getKraj() const{
	return this->kraj;
}

int PCB::getNeogr() const{
	return this->neogr;
}

Time PCB::getVreme() const{
	return this->vreme;
}

int PCB::getBlkNeo() const{
	return this->blkNeo;
}

Time PCB::getVrBlk() const{
	return this->vrBlk;
}

int PCB::getOdblkSig() const{
	return this->odblkSig;
}

void PCB::setStart(int s){
	this->start=s;
}

void PCB::setKraj(int k){
	this->kraj=k;
}

void PCB::setNeogr(int n){
	this->neogr=n;
}

void PCB::setVreme(Time t){
	this->vreme=t;
}

void PCB::setVrBlk(Time t){
	this->vrBlk=t;
}

void PCB::setBlkNeo(int i){
	this->blkNeo=i;
}

void PCB::setOdblkSig(int i){
	this->odblkSig=i;
}

unsigned PCB::getSP() const{
	return this->sp;
}

unsigned* PCB::getStek() const{
	return this->stek;
}

unsigned PCB::getBP() const{
	return this->bp;
}

unsigned PCB::getSS() const{
	return this->ss;
}

void PCB::setSS(unsigned s){
	this->ss=s;
}

void PCB::setSP(unsigned s){
	this->sp=s;
}

void PCB::setBP(unsigned s){
	this->bp=s;
}

void PCB::setStek(unsigned *s){
    this->stek=s;
}

int PCB::getBlock() const{
	return this->blocked;
}

void PCB::setBlock(int b){
	this->blocked=b;
}

ID PCB::getRunningId(){
	return ((PCB*)PCB::running)->getId();
}

Thread* PCB::getThreadById(ID id){
	return ((LstAkt*)PCB::lA)->getElById(id)->getThr();
}

void PCB::waitToCmp(){
	lock();
    if(this->getStart()==0){
		unlock();
		return;
	}

    if(((PCB*)PCB::running)->getId()!=this->getId()){
       if(this->getKraj()==0){
    	  ((PCB*)PCB::running)->setBlock(1);
          ((LstBlk*)this->lB)->dodaj(((PCB*)PCB::running));
    	  unlock();
    	  dispatch();
    	  return;
       }

       unlock();
       return;
    }

    unlock();
    return;
}

void PCB::startThread(){
	if(this->getStart()>=1){
	   return;
	}

	else{
	   lock();
	   this->setStart(1);
	   Scheduler::put(this);
	   unlock();
	}
}

void PCB::mainWaitAllToFinish(){
	if(((PCB*)PCB::running)->getStart()!=2){
		return;
	}
	((LstAkt*)PCB::lA)->mainWaitAll();
}
