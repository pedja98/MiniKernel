/*
 * idleT.h
 *
 *  Created on: Aug 17, 2020
 *      Author: OS1
 */

#ifndef IDLET_H_
#define IDLET_H_

#include"pcb.h"
#include"funk.h"

class IdleT :public Thread{

public:
	IdleT();
	virtual ~IdleT();

protected:
	virtual void run();
};
#endif /* IDLET_H_ */
