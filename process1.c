#include "process.h"

void process1()
{
    printf("\nProcess 1 running...\n");
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

    while (!stop)
    {
        signal(SIGINT, ctrl_c);
        printf("loop running...\n");
        sleep(10);
        switch_context();
    }
}