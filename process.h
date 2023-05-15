#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>

#define TIMEOUT_SECONDS 0
#define TIMEOUT_MICROSECONDS 0
#define l 10

struct PCB
{
    int process_id; //Process ID
    int priority; //Process Priority
    int state; //Process State
    int process_counter; //Process counter value
    int nextPCB;
    int registers[16];
    int memory[8];
};
char c;
void ctrl_c(int sig)
{
    if (sig == SIGINT)
    {
        printf("CTRL+C.\n");
        sleep(0);
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

struct PCB processes[3];
int current_process = 0;
void process1();
void process2();
void process3();
void context_switch();
#endif