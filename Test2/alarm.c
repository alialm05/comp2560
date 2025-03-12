#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <stdlib.h> 

void AlarmHandler(){
    static int n = 0;
    
    if(n++ < 5 ){
        printf("Got alarm signal, so far %d times\n", n);
        alarm(4);
    }

    else exit(0);
}

int main(int argc, char *argv[]){

    signal(SIGALRM, AlarmHandler); //install handler
    alarm(4);
    while(1){
        pause();
        printf("Got awaken by a SIGALRM\n");

    }
}