/*
 * thread.cpp
 *
 *  Created on: Jul 27, 2020
 *      Author: OS1
 */

#include"pcb.h"
#include "funk.h"

Thread::Thread (StackSize stackSize, Time timeSlice){
	lock();
	this->myPCB=new PCB(this, stackSize, timeSlice, 0);
	unlock();
}

Thread::~Thread(){
	this->waitToComplete();
	lock();
	delete this->myPCB;
	unlock();
}

ID Thread::getId(){
	return this->myPCB->getId();
}

ID Thread::getRunningId(){
	return PCB::getRunningId();
}

void Thread::start(){
	this->myPCB->startThread();
}

Thread * Thread::getThreadById(ID id){
	return PCB::getThreadById(id);
}

void Thread::waitToComplete(){
    this->myPCB->waitToCmp();
}

extern volatile int zahtev;

void dispatch (){
	asm cli;
	zahtev=1;
	timer();
	asm sti;
}

