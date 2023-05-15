#include "process.h"

#define m 2
#define n 2

void process2()
{
    printf("Process 2 running...\n");
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
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    while (1)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval timeout;
        timeout.tv_sec = TIMEOUT_SECONDS;
        timeout.tv_usec = TIMEOUT_MICROSECONDS;

        int ready = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

        if (ready == -1) {
            perror("select");
            break;
        } else if (ready == 0) {
            printf("loop running...\n");
        } else {
            if (read(STDIN_FILENO, &c, 1) == 1) {
                if (c == 27) { 
                    printf("ESC key pressed. Stopping the loop.\n");
                    break;
                } else {
                    printf("Key pressed: %c\n", c);
                }
            }
        }
        sleep(1);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    processes[1].process_counter++;

    // Check for process state transition
    if (processes[1].process_counter >= 15)
    {
        processes[1].state = 0;
        processes[2].state = 1;
    }
}
