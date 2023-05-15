#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>
#include "process3.c"
int main()
{
    process3();
}