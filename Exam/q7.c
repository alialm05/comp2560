#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    char name1[15] = "Bonjour\n";
    char name2[15] = "Bonsoir\n";
    fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC);
    write(fd, name1, 8);
    close(fd);
    fd = open("file.txt", O_RDONLY);
    dup2(fd, 0);
    read(0, name2, 8);
    write(1, name2, 8);
}