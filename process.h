#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <setjmp.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>

#define STACK_SIZE 1024
#define TIMEOUT_SECONDS 0
#define TIMEOUT_MICROSECONDS 0
#define l 10

typedef struct {
    int pid;
    int pc;
    int stack[STACK_SIZE];
    sigjmp_buf jmpbuf;
} PCB;

PCB *current_process;
PCB processes[3];

char c;
volatile sig_atomic_t stop = 0;
void ctrl_c(int sig)
{
    if (sig == SIGINT)
    {
        printf("CTRL+C.\n");
        stop = 1;;
    }
}

void ctrlcpause(int sig)
{
    if (sig == SIGINT)
    {
        printf("CTRL+C.\n");
        signal(SIGINT, SIG_DFL);
        sleep(5);
    }
}

void process1();
void process2();
void process3();
void switch_context();
#endif