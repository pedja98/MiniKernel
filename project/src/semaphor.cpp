/*
 * semaphor.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: OS1
 */

#include "semaphor.h"
#include "KerSem.h"

Semaphore::Semaphore(int init){
	lock();
	this->myImpl=new KernalSem(0,init);
	unlock();
}

Semaphore::~Semaphore(){
	lock();
	delete this->myImpl;
	unlock();
}

int Semaphore::wait(Time maxTimeToWait){
   return this->myImpl->wait(maxTimeToWait);
}

int Semaphore::signal(int n){
	return this->myImpl->signal(n);
}

int Semaphore::val() const{
	return this->myImpl->getVal();
}


