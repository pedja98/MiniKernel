/*
 * pcb.h
 *
 *  Created on: Jul 27, 2020
 *      Author: OS1
 */
#ifndef PCB_H_
#define PCB_H_

#include <iostream.h>
#include <dos.h>
#include "LstAkt.h"
#include "LstBlk.h"
#include "SCHEDULE.H"

class PCB{

private:
	int id;
	static int Iden;
	Thread *myThread;
	Time vreme;
	int start;
	int kraj;
	int neogr;
	int blocked;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned *stek;
	Time vrBlk;
	int blkNeo;
	int odblkSig;

public:
  volatile static int brPCB;
  volatile LstBlk *lB;
  volatile static LstAkt* lA;
  static volatile PCB* running;

  static void wrapper();
  static ID getRunningId();
  static Thread* getThreadById(ID id);

  void mainWaitAllToFinish();
  PCB(Thread* t,StackSize stackSize, Time timeSlice, int st);
  ID getId() const;
  int getStart() const;
  int getKraj() const;
  int getNeogr() const;
  int getBlock() const;
  int getBlkNeo() const;
  int getOdblkSig() const;
  Time getVreme() const;
  Time getVrBlk() const;
  unsigned* getStek() const;
  unsigned getSP() const;
  unsigned getSS() const;
  unsigned getBP() const;
  Thread* getThr() const;
  void setBlock(int b);
  void setStart(int s);
  void setKraj(int k);
  void setNeogr(int n);
  void setVreme(Time t);
  void setVrBlk(Time t);
  void setOdblkSig(int i);
  void setBlkNeo(int i);
  void setSS(unsigned s);
  void setSP(unsigned s);
  void setBP(unsigned s);
  void setStek(unsigned *s);
  void waitToCmp();
  void startThread();
  ~PCB();

};

#endif /* PCB_H_ */
