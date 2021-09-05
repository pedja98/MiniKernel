/*
 * thread.h
 *
 *  Created on: Jul 27, 2020
 *      Author: OS1
 */
#ifndef _thread_h_
#define _thread_h_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time;
const Time defaultTimeSlice = 2;
typedef int ID;

class PCB;

class Thread {

public:
   void start();
   void waitToComplete();
   virtual ~Thread();

   ID getId();
   static ID getRunningId();
   static Thread * getThreadById(ID id);

protected:
   friend class PCB;
   Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
   virtual void run() {}

private:
   PCB* myPCB;

};

void dispatch ();

#endif
