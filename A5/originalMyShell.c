#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <sys/wait.h>
pid_t myFork();
void readArgs(const char *, char *[]);
int main(int argc, char *argv[])
{
    pid_t pid;
    char line[255];
    char *argList[20];
    int status, i;
    printf("This program executes commands/programs for you\n");
    while (1)
    {
        printf("Enter CTR-C to exit, or enter\n");
        printf("a program name with its arguments> ");
        fgets(line, 255, stdin);
        readArgs(line, argList);
        
        if ((pid = myFork()) == -1)
        {
            perror("impossible to fork");
            exit(1);
        }
        if (pid > 0)
        { // This is the parent
            waitpid(pid, &status, 0);
            printf("My child has terminated\n");
        }
        else // this is the child
            if (execvp(argList[0], argList) == -1)
            {
                perror("child Process");
                exit(22);
            }
    }
    exit(0);
}
pid_t myFork()
{
    static int count = 0;
    if (count++ <= 20)
        return (fork());
    else
        return (-1);
}
void readArgs(const char *line, char *argList[])
{
    static int yes = 0;
    int i = 0, offset = 0;
    char name[50];
    while (yes & argList[i] != NULL)
        free(argList[i++]);
    i = 0; // reset i to ZERO
    while (sscanf(line + offset, "%s", name) == 1)
    {
        argList[i] = (char *)malloc(strlen(name) + 1);
        strcpy(argList[i++], name);
        while (line[offset] ==' ')
            offset++; // skip blanks
        offset += strlen(name);
    }
    argList[i] = NULL;
    yes = 1;
}