#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(){
    int n, status;

    if(fork())
        n=100;
    else
        n=200;

    wait(&status);
    printf("%d\n", n);
    exit(0);
}