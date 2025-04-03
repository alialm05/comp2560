#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void question3(){
    int i;
    for(i=1; i<=3; i++){
        fork();
        printf("Hello\n");
    }
    printf("Hello\n");
}

void question2(){
    
    fork();
    printf("HEllo ");
    fork();
    printf("HEllo\n");

}

void action(){
    fprintf(stderr, " Thursday ");
    exit(1);
}

void question5(){ // waits 1, prints thursday, then exist, then parents prints FInal

    pid_t pid, st;
    
    if(!(pid=fork())){
        signal(SIGALRM, action);
        alarm(1);
    
        while(1)
            sleep(1);
        
        fprintf(stderr, "exam ");
    }
    else{
        fprintf(stderr, "Final");
        wait(&st);
        fprintf(stderr, "%d\n", WEXITSTATUS(st));
    }

}

int main(){
    question5();

} 
