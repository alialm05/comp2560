#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define LineLength 128

int childFunction(){
    printf("child function");
}

int main(){    
    
    char sentenceBuf[LineLength];
    pid_t pid;

    
    setvbuf(stdin, sentenceBuf, _IOLBF, (size_t)LineLength);
    printf("This program is a text processing tool!\n");

    pid = fork();
    int status;

    if (pid > 0){
        printf("parent\n");
        wait(&status);
        childFunction();
    }
    else
        printf("child\n");
        while (1){
        
            printf("Enter a sentance, eg., Good day, my name is BigFoot\n");

            int bytesRead = read(STDIN_FILENO, sentenceBuf, LineLength);
            //sleep(2);
            break;
        }



    return 0;
}