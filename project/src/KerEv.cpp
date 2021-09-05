/*
 * KerEv.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: OS1
 */

#include"KerEv.h"
#include"funk.h"

KernelEv::KernelEv(IVTNo ivtNo){
	lock();
	this->vlasnik=Thread::getRunningId();
	this->entry=IVTEntry::getEntry(ivtNo);
	unlock();
}

KernelEv::~KernelEv(){
	this->entry=0;
}

void KernelEv::signal(){
	this->entry->signal();
}

void KernelEv::wait(){
	if(this->vlasnik!=Thread::getRunningId()){
		return;
	}
	this->entry->wait();
}
