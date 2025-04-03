#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char message[100];
    int n, server;
    struct sockaddr_in servAdd;
    server = socket(AF_INET, SOCK_STREAM, 0);
    servAdd.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servAdd.sin_addr);
    connect(server, (struct sockaddr *)&servAdd, sizeof(servAdd));
    n = read(server, message, 100);
    write(1, message, n);
    exit(0);
}