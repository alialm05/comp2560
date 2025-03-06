#include <stdio.h>
#include <fcntl.h>

#define BufferSize 100

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

int myFgets(char * buf, int size, int stream){
    
    int charCount = 0;

    do
    {
        int n = read(stream, buf+charCount, 1);

        if (n < 0){ // error
            perror("error reading file\n");
            return -1;
        }

        if (n == 0){ // EOF
            break;
        }

        if (buf[charCount] == '\n'){ // newline
            charCount++;
            break;
        }

        charCount++;
    } while (charCount < size-1);

    if (charCount == size-1){
        printf("buffer full\n");
    }
    
    buf[charCount] = '\0';
    //printf("last terminating char: [%d]: %s\n", charCount, buf+charCount);
    //displayBuffer(buf);

    return charCount;
}

int myFputs(const char *buf, int stream){

    int bi = 0;
    while (buf[bi] != EOF && buf[bi] != '\0'){
        //printf("#%d OUTPUTTED: %c  \n", bi, buf[bi]);
        write(stream, buf+bi, 1);
        bi++;
    }

}

int main(int argc, char *argv[]){
    
    if (argc < 2){
        printf("Please provide a source and destination file\nSynopsis: myCopy <source-file> <destination-file>");
        return 1;
    }
   
    int fd = open(argv[1], O_RDONLY | O_CREAT);
    int ofd = open(argv[2], O_WRONLY | O_CREAT);

    //int fd = open("thing.txt", O_RDONLY);
    //int ofd = open("output_thing.txt", O_WRONLY);

    char buffer[BufferSize] = {0};

    while (myFgets(buffer, BufferSize, fd) > 0){
        displayBuffer(buffer);
        myFputs(buffer, ofd);
    }

    return 0;
}