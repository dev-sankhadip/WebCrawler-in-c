#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <sys/stat.h>

bool ifDirectoryExists(char *path)
{
    // printf("%s", path);
    struct stat s;
    int err=stat(path,&s);
    // printf("%d", err);
    if(err==-1){
        return false;
    }
    return true;
}

char getWebPage(char *url)
{

}

int main(int argc, char *argv[])
{
    //there should be 3 arguments URL and desired directory
    if(argc<3)
    {
        fprintf(stderr,"There should be 3 arguments");
        exit(EXIT_FAILURE);
    }

    //check if given directory arguments exists
    if(!ifDirectoryExists(argv[2]))
    {
        printf("Not vald path");
    }

    if(getWebPage(argv[1]))
    {

    }
}