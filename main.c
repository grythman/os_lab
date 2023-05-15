#include "process.h"
#include "process1.c"
#include "process2.c"
#include "process3.c"

int main()
{
    // Initialize the processes
    processes[0].process_id = 1;
    processes[0].priority = 1;
    processes[0].state = 1;
    processes[0].process_counter = 0;
    processes[0].nextPCB = 0;

    processes[1].process_id = 2;
    processes[1].priority = 2;
    processes[1].state = 0;
    processes[1].process_counter = 0;
    processes[1].nextPCB = 0;

    processes[2].process_id = 3;
    processes[2].priority = 3;
    processes[2].state = 0;
    processes[2].process_counter = 0;
    processes[2].nextPCB = 0;

    // Set up signal handler for SIGINT (CTRL+C)
    signal(SIGINT, ctrl_c);

    while (1)
    {
        // Check if the current process is in running state
        if (processes[current_process].state == 1)
        {
            // Save the register values and other necessary state
            // ...

            // Set the state of the current process to ready
            processes[current_process].state = 0;
        }

        // Switch to the next process
        current_process++;
        if (current_process == 3)
        {
            current_process = 0;
        }

        // Set the state of the next process to running
        processes[current_process].state = 1;

        // Restore the state of the next process if it was previously saved
        if (processes[current_process].state == 1)
        {
            // Restore the register values and other necessary state
            // ...
        }

        // Set the program counter to the start of the next process
        switch (current_process)
        {
        case 0:
            process1();
            break;
        case 1:
            process2();
            break;
        case 2:
            process3();
            break;
        }
    }

    return 0;
}