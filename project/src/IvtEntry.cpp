/*
 * IvtEntry.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: OS1
 */

#include "IvtEntry.h"
#include "funk.h"
#include<dos.h>

IVTEntry ** IVTEntry::et=0;

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt prekid):s(0){
	lock();
	this->staraRutina=0;

	if(IVTEntry::et==0){
		IVTEntry::et=new IVTEntry*[256];
	}

	unlock();
	IVTEntry::et[ivtNo]=this;
	this->brojUlaza=ivtNo;
#ifndef BCC_BLOCK_IGNORE
	this->staraRutina=getvect(ivtNo);
	setvect(ivtNo,prekid);
#endif

}

IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	setvect(this->brojUlaza,this->staraRutina);
#endif
}

void IVTEntry::signal(){
	if(this->s.val()==1){
		return;
	}

	this->s.signal(1);
}

void IVTEntry::wait(){
	this->s.wait(0);
}

IVTEntry* IVTEntry::getEntry(IVTNo ivtNo){
	return IVTEntry::et[ivtNo];
}

void IVTEntry::pozoviStaru(){
	(*this->staraRutina) ();
}
