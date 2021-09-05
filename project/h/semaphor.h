/*
 * semaphor.h
 *
 *  Created on: Aug 17, 2020
 *      Author: OS1
 */

#ifndef semaphor_h_
#define semaphor_h_

typedef unsigned int Time;

class KernalSem;

class Semaphore{

public:
	Semaphore(int init=1);
	virtual ~Semaphore();
	virtual int wait(Time maxTimeToWait);
	virtual int signal(int n=0);
	int val() const;

private:
	KernalSem *myImpl;
};
#endif
