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
    }
}