#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void cancel(int signr)
{
    printf("Signal empfangen\n");
    printf("Ich beende mich aber nicht\n");
    fflush(stdout);
}


int main()
{
    pid_t pid = getpid();
    printf("%d\n", pid);

    signal(15, cancel);

    while(1)
    {
        ;
    }

    return 0;
}
