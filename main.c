#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <sys/select.h>
#include <signal.h>
#include <setjmp.h>

#define STACK_SIZE 4096
#define TIMEOUT_SECONDS 5
#define TIMEOUT_MICROSECONDS 0

typedef struct {
    int pid;
    int pc;
    int stack[STACK_SIZE];
    sigjmp_buf jmpbuf;
} PCB;

int stop = 0;
PCB *current_process;
PCB processes[3];

void switch_context()
{
    if (sigsetjmp(current_process->jmpbuf, 1) == 0)
    {
        int next_pid = (current_process->pid % 3) + 1;
        if (next_pid == 1)
        {
            current_process = &processes[0];
        }
        else if (next_pid == 2)
        {
            current_process = &processes[1];
        }
        else
        {
            current_process = &processes[2];
        }
        siglongjmp(current_process->jmpbuf, 1);
    }
}

void ctrl_c(int signum) {
    printf("\nCtrl+C detected. Stopping the loop.\n");
    stop = 1;
}

void ctrlcpause(int signum) {
    printf("\nCtrl+C detected. Pausing the loop.\n");
    signal(SIGINT, SIG_DFL);
    sleep(5);
}

void process1() {
    printf("Process 1 running...\n");
    int n = 10, a[n], i, j, temp;
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        a[i] = rand() % n;
        printf("%d ", a[i]);
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    printf("\nSorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    while (!stop) {
        signal(SIGINT, ctrl_c);
        printf("Process 1 loop running...\n");
        sleep(10);
        switch_context();
    }
}

#define m 2
#define n 2

void process2() {
    printf("Process 2 running...\n");
    int A[m][n], B[m][n], C[m][n];
    int i, j;
    char c = ' ';

    srand(time(NULL));
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    printf("Matrix 1:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("Matrix 2:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    printf("C matrices:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
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

    while (1) {
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
            printf("Process 2 loop running...\n");
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

        sleep(5);
        switch_context();
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

#define l 10

void process3() {
    printf("Process 3 running...\n");
    char str[l + 1];
    int count = 0;
    const char chr[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int s = sizeof(chr) - 1;
    srand(time(NULL));

    printf("Enter a string of length %d: ", l);
    for (int i = 0; i < l; i++) {
        int ind = rand() % s;
        str[i] = chr[ind];
    }
    str[l] = '\0';
    printf("%s\n", str);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == str[rand() % strlen(str)]) {
            count++;
        }
    }

    signal(SIGINT, ctrlcpause);

    while (1) {
        printf("Process 3 loop running... %d matching pairs found.\n", count);
        sleep(3);
        if (sigsetjmp(current_process->jmpbuf, 1) == 0) {
            switch_context();
        }
    }
}
int main()
{
    current_process = &processes[0];
    processes[0].pid = 1;
    processes[0].pc = 0;
    sigemptyset(&processes[0].jmpbuf->__saved_mask);
    sigaddset(&processes[0].jmpbuf->__saved_mask, SIGINT);
    sigsetjmp(processes[0].jmpbuf, 1);

    processes[1].pid = 2;
    processes[1].pc = 0;
    sigemptyset(&processes[1].jmpbuf->__saved_mask);
    sigaddset(&processes[1].jmpbuf->__saved_mask, SIGINT);
    sigsetjmp(processes[1].jmpbuf, 1);

    processes[2].pid = 3;
    processes[2].pc = 0;
    sigemptyset(&processes[2].jmpbuf->__saved_mask);
    sigaddset(&processes[2].jmpbuf->__saved_mask, SIGINT);
    sigsetjmp(processes[2].jmpbuf, 1);

    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrlcpause);

    if (current_process->pid == 1)
    {
        process1();
    }
    else if (current_process->pid == 2)
    {
        process2();
    }
    else if (current_process->pid == 3)
    {
        process3();
    }

    return 0;
}
