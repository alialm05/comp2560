#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>

int isFile(char *path){
    struct stat pathStat;
    stat(path, &pathStat);

    return S_ISREG(pathStat.st_mode);
}

int main(int argc, char *argv[]){
    DIR *dp;
    struct dirent *dirp;
    
    if(argc==1)
        dp = opendir("./");
    else
        dp = opendir(argv[1]);
    
    while ( (dirp=readdir(dp)) != NULL){
        printf("%s", dirp->d_name);
        
        if(!isFile(dirp->d_name))
            printf("/");
       
        printf("\n");
    }
    
    closedir(dp);
    exit(0);
}
