#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void action(){
    fprintf(stderr, " Thursday ");
    exit(1);
}

void main(){ // waits 1, prints thursday, then exist, then parents prints FInal

    pid_t pid, st;
    
    if(!(pid=fork())){
        signal(SIGALRM, action);
        alarm(1);
    
        while(1)
            sleep(1);
        
        fprintf(stderr, "exam "); // not printed because it will exit before
    }
    else{
        fprintf(stderr, "Final");
        wait(&st);
        fprintf(stderr, "%d\n", WEXITSTATUS(st));
    }

}
