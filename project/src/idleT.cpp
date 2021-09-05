/*
 * idleT.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: OS1
 */

#include "idleT.h"

IdleT::IdleT():Thread(){}

IdleT::~IdleT(){
	 this->waitToComplete();
}

void IdleT::run(){
	while(1){
	}
}

