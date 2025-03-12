#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void myHandler(){}; // to avoid quiting

int main(int argc, char *argv[]){
    pid_t pid;
    signal(SIGUSR1, myHandler);

    if((pid=fork()) > 0){
        printf("Parent: child waits until I’m done\n");
        sleep(4);
        printf("Parent: child can do its job now\n");
        kill(pid, SIGUSR1); // let the child wake up
        printf("Parent: Exiting\n");
    }else{
        printf("Child: I have to wait for my parent\n");
        pause();
        printf("Child: now I can do my job\n");
        sleep(2);
        printf("\nChild: Exiting now\n");
    }
    exit(0);
}