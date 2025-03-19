#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <sys/wait.h>

pid_t
myFork();
void readArgs(const char *, char *[]);
int getNextCommand(const char *, int*, char *);

int main(int argc, char *argv[]){
    
    char line[255];
    char command[255]; // indivisual command string
    int status, i;
    char *argList[20];
    
    printf("This program executes commands/programs for you\n");
    while (1){

        int offset = 0;
        
        printf("\nEnter CTR-C to exit, or enter\n");
        printf("a program name with its arguments> ");
        fgets(line, 255, stdin);

        while (getNextCommand(line, &offset, command) != -1){
            
            printf("\n%s\n", command);
            
            pid_t pid;
            readArgs(command, argList);
                
            //sleep(1);
            if ((pid = myFork()) == -1){
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
                }else {   // successfull exit
                    exit(0);
                }

        }

    }
    exit(0);
}

pid_t myFork(){
    static int count = 0;
    if (count++ <= 20)
        return (fork());
    else
        return (-1);
}

void readArgs(const char *line, char *argList[]){
    
    static int yes = 0;
    int i = 0, offset = 0; // offset of arguments
    char name[50];

    while (yes & argList[i] != NULL) // frees previous command memory
        free(argList[i++]);

    //printf("%s\n", line);
    //printf("\nargs: \n\t");

    i = 0; // reset i to ZERO
    while (sscanf(line + offset, "%s", name) == 1)
    {
        //printf("\n\t%s", name);
        argList[i] = (char *)malloc(strlen(name) + 1);
        strcpy(argList[i++], name);
        while (line[offset] == ' ')
            offset++; // skip blanks
        offset += strlen(name);
    }
    argList[i] = NULL;
    yes = 1;

}

int getNextCommand(const char * line, int* offset, char * command){
    
    memset(command, 0, sizeof command); // reset command string
    int i = *offset; // line index offset
    int ci = 0;     //  command string index

    if (line[i] == '\0'){ // end of line
        printf("\nEND OF LINE\n");
        return -1;
    }

    while (line[i] == ' ')
        i++;

    while (line[i] != '\0')
    {

        if (line[i] == ';'){
            i++;
            break;
        }
        
        command[ci] = line[i];

        ci++;
        i++;
    }

    command[i] = '\0';
    *offset = i;

    return ci; // read chars

}