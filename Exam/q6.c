#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void action()
{
    fprintf(stderr, "OK ");
    exit(0);
}
int main()
{
    pid_t pid;
    if (!(pid = fork()))
    {
        signal(SIGUSR1, action);
        pause();
        fprintf(stderr, "First "); // wont print
    }
    else
    {
        sleep(1);
        fprintf(stderr, "Thursday ");
        kill(pid, SIGUSR1);
    }
    sleep(1);
    fprintf(stderr, " Next ");
}