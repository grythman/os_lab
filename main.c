#include "process.h"


int main()
{

    while (1)
    {
        printf("hiih uildlee songono uu. \n");
        printf("1. Process1, 2. Process2, 3. Process3 , 4. Context-Switching\n");
        int t;
        scanf("%d", &t);
        switch (t)
        {
        case 1:
            process1();
            break;
        case 2:
            process2();
            break;
        case 3:
            process3();
            break;
        case 4:
            context_switch ();
            break;
        default:
            printf("Buruu songolt!");
            break;
        }
    }
    return 0;
}
