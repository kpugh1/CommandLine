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
void chooseFunction(int);
void fileconverter();
void create();
void indexer();
void quit();

//Function to execute fileconverter
void chooseFunction(int argCount)
{
	//Perform commands based on input
    //FILE CONVERTER COMMAND
	if(strcmp((char*)args[0], "fileconverter") == 0 && argCount == 3)
        {
            sprintf(outdirectory[directCount], "./%s/", (char*)args[2]);
            fileconverter();
            directCount++;
            
        //CREATE COMMAND
        }else if(strcmp((char *)args[0], "create") == 0 && argCount > 2 && argCount < 5)
        {
            if(strcmp((char*)args[1], "-d") == 0 && argCount == 3)
            {
                sprintf(outdirectory[directCount], "./%s/", (char*)args[2]);
                create();
                directCount++;
            }else if(strcmp((char*)args[1], "-f") == 0 && argCount == 3)
            {
                //sprintf(currFiles[fileCount], "./%s/", args[2]);
                strcpy(currFiles[fileCount], (char*)args[2]);
                create();
                fileCount++;
            }else if(strcmp((char*)args[1], "-h") == 0 && argCount == 4)
            {
                strcpy(currLinks[linkCount], (char*)args[3]);
                create();
                linkCount++;
            }else if(strcmp((char*)args[1], "-s") == 0 && argCount == 4)
            {
                strcpy(currLinks[linkCount], (char*)args[3]);
                create();
                linkCount++;
            }else
                printf("Wrong flag or wrong arg count. Please try again\n");
            
        //INDEXER COMMAND
        }else if(strcmp((char*)args[0], "indexer") == 0 && (argCount == 2 || argCount == 3))
        {
            if(argCount == 2)
            {
                sprintf(outdirectory[directCount], "./%s/", (char*)args[1]);
                indexer();
                directCount++;
            }else
            {
                sprintf(outdirectory[directCount], "./%s/", (char*)args[2]);
                indexer();
                directCount++;
            }
            
        //QUIT COMMAND
        }else if(strcmp((char*)args[0], "quit") == 0)
        {
            char c;
            printf("Are you sure you want to exit? All files will be lost. Enter Y to quit\n");
            scanf("%c", &c);
            c = toupper(c);
            if(c == 'Y')
                quit();
			else
			{
				printf("Returning to main menu\n");
			}

        }else
            printf("Invalid selection: enter again or check # of arguments\n");
}

//Function for fileconverter executable
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
    char *argv[] = {"./create", (char*)args[1], (char*)args[2], (char*)args[3], NULL};
    
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