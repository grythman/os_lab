#include "process.h"

void switch_context()
{
    // Save the current process's context
    if (current_process != NULL)
    {
        if (setjmp(current_process->stack) == 0)
        {
            // Update the program counter to the next instruction
            current_process->pc = current_process->pc + 1;
            // Restore the saved process's context
            longjmp(processes[current_process->pc].stack, 1);
        }
    }
    // Find the next process to run
    int next_process = (current_process->pid + 1) % 3;
    // Set the current process to the next process
    current_process = &processes[next_process];
    // Start or resume the next process
    longjmp(current_process->stack, 1);
}