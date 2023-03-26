#include "process.h"




int main()
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
    while(1)
    {
        printf("Hello World\n");
    }
    return 0;
}