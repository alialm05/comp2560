#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    printf("Hello\n");
    fork();
    printf("WINdsor\n");
    pause();
    exit(0);
}
