#include "process.h"

#define m 2
#define n 2

void ctrl_c(int sig)
{
    if (sig == SIGINT)
    {
        printf("CTRL+C.\n");
        sleep(5);
    }
}

void process2()
{
    int A[m][n], B[m][n], C[m][n];
    int i, j;
    char c = ' ';

    srand(time(NULL));
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    printf("Matrix 1:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("Matrix 2:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    printf("C matrices:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    signal(SIGINT, ctrl_c);
    while (c != 27)
    {
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
        if (kbhit())
        {
            c = getchar();
            printf("Key pressed: %c\n", c);
            sleep(5);
        }
        processes[1].pcount++;
        printf("Process 2 running (count = %d)\n", processes[1].pcount);

        srand(time(NULL));
        int rand_num = rand() % 100;

        if (rand_num % 2 == 0)
        {
            processes[1].state = 0;
            processes[2].state = 1;
            //running_process = 2;
            break;
        }
    }
}
