#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int pid;
    printf("Only one process\n");
    pid = fork();
    
    if(pid == -1){
        perror("impossible to fork");
        exit(1);
    }
    
    if(pid > 0){
        printf("I am the parent, pid=%d\n", getpid());
        sleep(2);
    }
    else if(pid == 0){
        while (1)
        {
            sleep(1);
            printf("I am the child, pid=%d\n", getpid());
        }
        
    }


    exit(0);

}