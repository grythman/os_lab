#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



struct PCB { 
   int pid; 
   int priority; 
   int state; 
   int pcount; 
   int registers[16]; 
   int memory[8]; 
   int nextPCB;
};

int c;

struct PCB processes[3];
//int running_process = 0;
//process2

//process3
void process1();
void process2();
void process3();
void context_switch();
#define l 10
#endif