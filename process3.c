#include "process.h"

void process3()
{
    char str[l + 1];
    int count = 0;
    const char chr[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int s = sizeof(chr) - 1;
    srand(time(NULL));

    printf("temdegt mur oruulna uu: ");
    for (int i = 0; i < l; i++)
    {
        int ind = rand() % s;
        str[i] = chr[ind];
    }
    printf("Random string: %s\n", str);
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == str[rand() % strlen(str)])
        {
            count++;
        }
    }
    signal(SIGINT, CTRLC);
    while (1)
    {
        printf("temdegt mur dotor %d shirheg ijil useg ollo.\n", count);
        processes[2].pcount++;
        printf("Process 3 running (count = %d)\n", processes[2].pcount);

        srand(time(NULL));
        int rand_num = rand() % 100;

        if (rand_num % 2 == 0)
        {
            processes[2].state = 0;
            processes[0].state = 1;
            running_process = 0;
            break;
        }
        if (kbhit())
        {
            c = getchar();
            printf("Key pressed: %c\n", c);
            sleep(5);
        }
    }
}