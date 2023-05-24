#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void cancel(int nr)
{
    printf("Signal erkannt...");
    printf("Ich beende mich trotzdem nicht.\n");
    fflush(stdout);
}


int main()
{

    pid_t pid = getpid();
    printf("PID: %d\n", pid);

    signal(15, cancel);

    while(1)
    {
        ;
    }

    return 0;
}
