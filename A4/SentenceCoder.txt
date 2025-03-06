#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BufferSize 1024
#define LCAsciiStart 97
#define UCAsciiStart 65

void displayBuffer(char *buffer){
    int i = 0;
    printf("\nBUFFER: \n");
    while (buffer[i] != EOF && buffer[i] != 0){
        printf("\t[%d]: %c\n", i, buffer[i]);
        i++;
    }
    
    if (i < BufferSize){
        printf("\t[%d]: %c\n", i, buffer[i]);
    }
    printf("\n\n");
}

int writeToFile(char *buffer, int count){
    int ofd = open("code.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (write(ofd, buffer, count) < 0){
        perror("Error writing to file\n");
        exit(1);
    };

    close(ofd);
    exit(0);
}

int codeSentence(char *buffer, int count){
    
    int i = 0;
    
    while (i < count){
        if (buffer[i] >= LCAsciiStart &&  buffer[i] <= LCAsciiStart+26){
            buffer[i]-=32;
        }else
            if (buffer[i] >= UCAsciiStart &&  buffer[i] <= UCAsciiStart+26) {
                buffer[i]+=32;
        }
        i++;
    }

    writeToFile(buffer, count);
}

int childFunction(char *buffer, int count){
    sleep(1);
    printf("\n\t-> I am a child proccess working for my parent\n\n");
    
    //displayBuffer(buffer);
    if (count <= 1){
        exit(55);
    }

    codeSentence(buffer, count);
}

int outputCode(int byteCount){
    int ofd = open("code.txt", O_RDONLY);
    char b[BufferSize];
    
    if (read(ofd, b, byteCount) < 0){
        perror("Error reading code\n");
        return 1;
    }
    printf("%s", b);

    close(ofd);
}

int main(){    
    
    pid_t pid;

    printf("This program is a text processing tool!\n");
    
    while (1){
        
        char sentenceBuf[BufferSize] = {0};
        printf("\nEnter a sentance, eg., Good day, my name is BigFoot\n");
    
        int bytesRead = read(STDIN_FILENO, sentenceBuf, BufferSize);

        if (bytesRead < 0){
            perror("Error reading from keyboard\n");
            return 1;
        }

        pid = fork();
        int status;
    
        if (pid > 0){ // Parent
            printf("\nI just created a child to preform a task for me, waiting for the child\n");
            wait(&status);


            if (WIFEXITED(status)){
                if (WEXITSTATUS(status) == 55) {
                    printf("Error, sentence Missing!\n");
                }else if (WEXITSTATUS(status) == 0) {
                    printf("Done!\nCoded Sentence:\n\n");
                    outputCode(bytesRead);
                }
            }
            else{
                printf("Something Went Wrong\n");
            }
        }
        else  { // Child
            childFunction(sentenceBuf, bytesRead);
        }

        sleep(1);

    }    



    return 0;
}