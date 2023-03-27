#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>

struct PCB { 
   int pid; 
   int priority; 
   int state; 
   int pcount; 
   int registers[16]; 
   int memory; 
   int nextPCB;
};
//process2

//process3
#define l 10
void CTRLC(int sig);
#endif