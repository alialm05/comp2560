#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(void){
    int pid;
    pid=fork();
    alarm(3);
    
    if(!pid){
        sleep(2);
        printf("Saturday\n");
    }else
        printf("Today\n");

    sleep(1);
    printf("Tomorrow\n");
    exit(0);
}