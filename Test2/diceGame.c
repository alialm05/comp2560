#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

void action(){}; // Example: two-player game
void player(char *);

int main(int argc, char *argv[]){

    pid_t pid1, pid2;
    printf("This is a 2-players game with a referee\n");
    signal(SIGUSR1, action);
    if((pid1=fork()) == 0) player("TOTO");
    if((pid2=fork()) == 0) player("TITI");

    sleep(1);

    while(1){
        printf("\nReferee: TOTO turn to play\n\n");
        kill(pid1, SIGUSR1);// let TOTO wake up
        pause();
        printf("\n\nReferee: TITI turn to play\n\n");
        kill(pid2, SIGUSR1);// let TITI wake up
        pause();
    }

    exit(0);
}

void player(char *s){
    int points=0, dice;
    while(1){
        pause(); // blocks itself

        printf("%s: playing my dice\n", s);
        dice =(int) time(NULL)%10 + 1;

        printf("%s: got %d points\n", s, dice);
        points+=dice;

        printf("%s: Total so far %d\n\n", s, points);
        sleep(3);

        if(points >= 20){
            printf("%s: game over I won\n", s);
            kill(0, SIGTERM); // terminate process group
        }

        kill(getppid(), SIGUSR1); // let referee wake up
    }
}