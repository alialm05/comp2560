#include <stdio.h>
#include <unistd.h>

int main(){
    fork();
    for(int i=0; i < 3; i++){
        if(!fork())
        printf("Hi - %d\n", i);
    }
}