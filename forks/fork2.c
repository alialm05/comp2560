#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void action(){
    sleep(2);
    printf("Switching\n");
}

int main(int argc, char *argv[]){
    pid_t pid;

    signal(SIGUSR1, action);
    
    pid=fork();
    sleep(1);

    if (pid > 0)
        while(1){
            printf("Parent: Running\n");
            kill(pid, SIGUSR1); // send signal to child
            pause();
        }
    
    else 
        //printf("Child: Proccess\n"); // remove brackets from if statments works? idk
        while(1){
            pause();
            printf("Child: Running\n");
            kill(getppid(), SIGUSR1);
        }
    
}