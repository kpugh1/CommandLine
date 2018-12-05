#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<dirent.h>
#include<string.h>

#define MAX_ARGS 4
#define MAX_ARG_SIZE 20

//Globals
extern pid_t pid;
extern int status;
extern int directCount, fileCount;
extern char *args[MAX_ARGS][MAX_ARG_SIZE];
extern char outdirectory[50][200];
extern char currFiles[50][200];

//Prototypes
void fileconverter();
void create();
void indexer();
void quit();

//Function to execute fileconverter
void fileconverter()
{
    printf("Starting file converter command\n");
    
    //Create filepath and arguments for executable
    char *argv[] = {"./fileconverter", args[1], outdirectory[directCount], NULL};
    
    if((pid = fork()) < 0)
    {
        printf("Could not open child\n");
    }else if(pid == 0)
    {
        if (execvp(argv[0], argv) < 0)
        {
            printf("Failed to execute fileconverter command\n");
        }

    }else
        waitpid(pid, &status, 0);
}

//Function to execute create
void create()
{
    printf("Starting create command\n");
    char *argv[] = {"./create", args[1], args[2], args[3], NULL};
    
    //Creating child process
    if((pid = fork()) < 0)
    {
        printf("Could not open child\n");
    }else if(pid == 0)
    {
        if(execvp(argv[0], argv) < 0)
            printf("Failed to execute create command\n");
    }else
        waitpid(pid, &status, 0);
}

//Function to execute indexer
void indexer()
{
    printf("Starting indexer command\n");
    char *argv[250];
    
    if(args[2][0] == '\0')
        sprintf(argv, "./indexer %s", outdirectory[directCount]);
    else
        sprintf(argv, "./indexer %s %s", args[1], outdirectory[directCount]);
        
    //Creating child process
    if((pid = fork()) < 0)
    {
        printf("Could not open child");
    }else if(pid == 0)
    {
        if(execvp(argv[0], argv) < 0)
            printf("Failed to execute indexer command\n");
    }else
        waitpid(pid, &status, 0);
}

//Quit Program
//NOT YET COMPLETE
void quit()
{
    printf("Deleting all files\n");
    int i = 0;
    
    //Remove all intermediate files in the parent directory
    while(currFiles[i][0] != '\0')
    {
        remove(currFiles[i]);
        i++;
    }
    
    i = 0;
    
    //Traverse through array of directories and delete all of them
    while(outdirectory[i][0] != '\0')
    {
        //open directory of flight records
        DIR *direct = opendir(outdirectory[i]);
    
        //if directory doesn't exist, exit program
        if(direct == NULL)
        {
            printf("Exiting program\n");
            exit(0);
        }
        
        struct dirent *next;
        char filepath[200];
        strcpy(filepath, outdirectory[i]);
    
        //delete all airline files within the directory
        while((next = readdir(direct)) != NULL)
        {
            strcat(filepath, next->d_name);
            remove(filepath);
            strcpy(filepath, outdirectory[i]);
        }
    
        //delete the directory itself
        rmdir(outdirectory[i]);
        
        i++;
    }

    
    printf("Exiting program\n");
    exit(0);
}