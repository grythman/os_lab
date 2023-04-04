#include "process.h"

void context_switch()
{
    int i;
    for (i = 0; i < 16; i++)
    {
        processes[running_process].registers[i] = rand() % 100;
    }
    for (i = 0; i < 8; i++)
    {
        processes[running_process].memory[i] = rand() % 100;
    }
    int next_process = processes[running_process].nextPCB;
    while (processes[next_process].state == 0)
    {
        next_process = processes[next_process].nextPCB;
    }

    running_process = next_process;

    for (i = 0; i < 16; i++)
    {
        rand() % 100;
    }
    for (i = 0; i < 8; i++)
    {
        rand() % 100;
    }

    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);

    if (running_process == 0)
    {
        process1();
    }
    else if (running_process == 1)
    {
        process2();
    }
    else
    {
        process3();
    }
}