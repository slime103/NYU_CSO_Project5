/*
*
*
*
* Compile with gcc -Wall problem2c.c -o problem2c
*
*
*/



#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int secs = 0;

void handle_sigint(int sig)
{
    secs = 0;
}

int main(int argc, char **argv)
{
    sleep(1);
    signal(SIGINT, handle_sigint);
    pid_t ppid = getppid();

    while (secs < 5)
    {
        printf("Time:%i\n",secs);
        fflush(0);
        sleep(1);
        secs++;
        printf("\r\b\r");
    }
    kill(ppid, SIGINT);

    return 0;
}