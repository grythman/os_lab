#include "process.h"


int main()
{
    processes[0].pid = 1;
    processes[0].priority = 1;
    processes[0].state = 1;
    processes[0].pcount = 0;
    processes[0].nextPCB = 1;

    processes[1].pid = 2;
    processes[1].priority = 2;
    processes[1].state = 0;
    processes[1].pcount = 0;
    processes[1].nextPCB = 2;

    processes[2].pid = 3;
    processes[2].priority = 3;
    processes[2].state = 0;
    processes[2].pcount = 0;
    processes[2].nextPCB = 0;

    signal(SIGALRM, context_switch);

    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);

    process1();

    while (1)
    {
        printf("hiih uildlee songono uu. \n");
        printf("1. Process1, 2. Process2, 3. Process3 , 4. Context-Switching\n");
        int t;
        scanf("%d", &t);
        switch (t)
        {
        case 1:
            process1();
            break;
        case 2:
            process2();
            break;
        case 3:
            process3();
            break;
        case 4:
            context_switch ();
            break;
        default:
            printf("Buruu songolt!");
            break;
        }
    }
    return 0;
}
