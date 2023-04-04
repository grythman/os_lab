#include "process.h"

void CTRLC(int sig)
{
    if (sig == SIGINT)
    {
        printf("CTRL+C.\n");
        exit(0);
    }
}

void process1()
{
    int n = 10, a[n], i, j, temp;
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        a[i] = rand() % n;
        printf("%d ", a[i]);
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    printf("\nEremblegdsen daraalal: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    signal(SIGINT, CTRLC);
    while (1)
    {
        processes[0].pcount++;
        printf("Process 1 running (count = %d)\n", processes[0].pcount);

        srand(time(NULL));
        int rand_num = rand() % 100;

        if (rand_num % 2 == 0)
        {
            processes[0].state = 0;
            processes[1].state = 1;
            running_process = 1;
            break;
        }
    }
}