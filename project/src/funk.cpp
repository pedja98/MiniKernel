/*
 * funk.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: OS1
 */

#include "funk.h"

unsigned oldTimerSEG, oldTimerOFF;

volatile int lck=0;
volatile int brProl=0;

volatile int zahtev=0;
volatile int zahtevanaPromena=0;

volatile int brBlokiranih=0;
volatile Time brojac;

volatile PCB *pcbMain;
volatile IdleT *iT;
volatile PCB *pcbIt;

unsigned tsp;
unsigned tss;
unsigned tbp;

void inic(){
    iT= new IdleT();
    ((IdleT*)iT)->start();
    pcbIt=Scheduler::get();

    brojac=1;
    pcbMain=new PCB(0,0,brojac,2);
    PCB::running=pcbMain;

    asm{
    	cli
    	push es
    	push ax

    	mov ax,0
    	mov es,ax

    	mov ax, word ptr es:0022h
    	mov word ptr oldTimerSEG, ax
    	mov ax, word ptr es:0020h
    	mov word ptr oldTimerOFF, ax

    	mov word ptr es:0022h, seg timer
    	mov word ptr es:0020h, offset timer

    	mov ax, oldTimerSEG
    	mov word ptr es:0182h, ax
    	mov ax, oldTimerOFF
    	mov word ptr es:0180h, ax

    	pop ax
    	pop es
    }
}

void restore(){
	((PCB*)PCB::running)->mainWaitAllToFinish();

	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}

	((PCB*)pcbIt)->setKraj(1);
	((LstBlk*)((PCB*)pcbIt)->lB)->isprLst();
	delete iT;

	((PCB*)pcbMain)->setKraj(1);
	((LstBlk*)((PCB*)pcbMain)->lB)->isprLst();
    delete pcbMain;

	delete PCB::lA;
	delete KernalSem::lS;
	delete[] IVTEntry::et;
}

extern void tick();

void lock(){
	lck=1;
	brProl++;
}

void unlock(){
   brProl--;

   if(brProl==0){
	   if(zahtevanaPromena==1){
		   lck=0;
		   dispatch();
	   }
	   else{
		   lck=0;
	   }
   }
}

void interrupt timer(...){
	if(zahtev==0){
		if(brojac>0){
		   brojac--;
		}
		((LstSem *)KernalSem::lS)->prolaz();
	}
	if((brojac==0 && ((PCB*)PCB::running)->getNeogr()==0 ) || zahtev==1){
		if(lck==0){
			zahtevanaPromena=0;
			asm {
			     mov tsp, sp
			     mov tss, ss
		         mov tbp, bp
			}
			((PCB*)PCB::running)->setBP(tbp);
		    ((PCB*)PCB::running)->setSP(tsp);
			((PCB*)PCB::running)->setSS(tss);
			if(((PCB*)PCB::running)->getId()==((PCB*)pcbIt)->getId() && brBlokiranih==PCB::brPCB){
				PCB::running=0;
			}
			if(((PCB*)PCB::running)->getKraj()==0 && ((PCB*)PCB::running)->getBlock()==0 && ((PCB*)PCB::running)->getId()!=((PCB*)pcbIt)->getId()){
			    Scheduler::put(((PCB*)PCB::running));
			}
			PCB::running=Scheduler::get();
			if(PCB::running==0){
				PCB::running=pcbIt;
			}
			tss=((PCB*)PCB::running)->getSS();
			tsp=((PCB*)PCB::running)->getSP();
			tbp=((PCB*)PCB::running)->getBP();
			brojac=((PCB*)PCB::running)->getVreme();
			asm {
			    mov sp, tsp
			    mov ss, tss
				mov bp, tbp
		    }
		}
		else{
			zahtevanaPromena=1;
		}
	}

	if(zahtev==0) asm int 60h;

	zahtev=0;

	tick();
}
