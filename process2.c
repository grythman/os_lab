#include "process.h"

#define m 2
#define n 2

void CTRLC(int sig) {
    if (sig == SIGINT) {
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
    signal(SIGINT, CTRLC);
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
            c = getch();
        }
    }
}
