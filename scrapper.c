#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <sys/stat.h>
#include<string.h>

bool ifDirectoryExists(char *path)
{
    struct stat statbuf;
    if ( stat(path, &statbuf) == -1 ) 
    {
        fprintf(stderr, "-----------------\n");
        fprintf(stderr, "Invalid directory\n");
        fprintf(stderr, "-----------------\n");
        // exit(1);
        return false;
    }

    //Both check if there's a directory and if it's writable
    if ( !S_ISDIR(statbuf.st_mode) ) 
    {
        fprintf(stderr, "-----------------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
        fprintf(stderr, "-----------------------------------------------------\n");
        // exit(1);
        return false;
    }

    if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR ) 
    {
        fprintf(stderr, "------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. It isn't writable\n");
        fprintf(stderr, "------------------------------------------\n");
        // exit(1);
        return false;
    }
    return true;
}

// bool ifValidUrl(char *url)
// {
//     char command[]="wget --spider ";
//     strcat(command,url);
//     if(system(command))
//     {
//         printf("URL validated");
//     }
//     else
//     {
//         printf("URL invalid");
//     }
// }

void moveToDesiredDir(char *path)
{
    printf("Hello");
    FILE *oldFilePtr, *newFilePtr;
    char newDIR[50],c;
    strcpy(newDIR, path);
    strcat(newDIR,"/");
    strcat(newDIR,"index.html");

    // open downloaded file in read mode
    oldFilePtr=fopen("file.txt","r");
    if(oldFilePtr==NULL)
    {
        printf("Can't open file");
        exit(EXIT_FAILURE);
    }

    //open new desired file for wrting content of crawled webpage
    newFilePtr=fopen(newDIR,"w");
    if(newFilePtr==NULL)
    {
        printf("Can't open file");
        exit(EXIT_FAILURE);
    }

    c=fgetc(oldFilePtr);
    while(c!=EOF)
    {
        fputc(c, newFilePtr);
        c=fgetc(oldFilePtr);
    }

    fclose(oldFilePtr);
    fclose(newFilePtr);

    printf("File copied successfully");
}


void crawlWebsite(char *url, char *path)
{
    char sysCommand[]="wget -O file.txt ";
    strcat(sysCommand,url);
    system(sysCommand);
    moveToDesiredDir(path);
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
        exit(EXIT_FAILURE);
    }

    printf("Valid directory");
    // if(!ifValidUrl(argv[1]))
    // {
    //     exit(EXIT_FAILURE);
    // }

    crawlWebsite(argv[1],argv[2]);

    moveToDesiredDir(argv[2]);

}