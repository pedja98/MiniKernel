/*
 * event.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: OS1
 */

#include "event.h"
#include "KerEv.h"
#include "funk.h"

Event::Event(IVTNo ivtNo){
	lock();
	this->myImpl=new KernelEv(ivtNo);
	unlock();
}

Event::~Event(){
	lock();
	delete this->myImpl;
	unlock();
}

void Event::wait(){
	this->myImpl->wait();
}

void Event::signal(){
	this->myImpl->signal();
}


