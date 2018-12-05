#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "interfaceFunctions.c"

#define MAX_CHOICE 50
#define MAX_ARGS 4
#define MAX_ARG_SIZE 20

pid_t pid;
int status;
int directCount, fileCount;
char *args[MAX_ARGS][MAX_ARG_SIZE];
char outdirectory[50][200];
char currFiles[50][200];

int main(int argc, char *argv[])
{
    //variables
    char *choice = malloc(MAX_CHOICE);
    char *token;
    int i = 0, argCount = 0;
    directCount = 0;
    fileCount = 0;
    
    memset(args, 0, sizeof(args));

    getInput(choice, MAX_CHOICE);
    
    //loop until user quits out of shell
    while(1)
    {
    
        //separate input into arg array using strtok()
        token = strtok(choice, " ");
        while(token != NULL && i < MAX_ARGS)
        {
            //printf("The token is: %s\n", token);
            strcpy(args[i], token);
            token = strtok(NULL, " ");
            i++;
            argCount++;
        }

        i = 0;
        
        //Perform commands based on user input
        //FILE CONVERTER COMMAND
        if(strcmp(args[0], "fileconverter") == 0 && argCount == 3)
        {
            sprintf(outdirectory[directCount], "./%s/", args[2]);
            fileconverter();
            directCount++;
            
        //CREATE COMMAND
        }else if(strcmp(args[0], "create") == 0 && argCount > 2 && argCount < 5)
        {
            if(strcmp(args[1], "-d") == 0 && args[2][0] != '\0')
            {
                sprintf(outdirectory[directCount], "./%s/", args[2]);
                create();
                directCount++;
            }else if(strcmp(args[1], "-f") == 0 && args[2][0] != '\0')
            {
                //sprintf(currFiles[fileCount], "./%s/", args[2]);
                strcpy(currFiles[fileCount], args[2]);
                create();
                fileCount++;
            }
            
        //INDEXER COMMAND
        }else if(strcmp(args[0], "indexer") == 0 && (argCount == 2 || argCount == 3))
        {
            if(argCount == 2)
            {
                sprintf(outdirectory[directCount], "./%s/", args[1]);
                indexer();
                directCount++;
            }else
            {
                sprintf(outdirectory[directCount], "./%s/", args[2]);
                indexer();
                directCount++;
            }
            
        //QUIT COMMAND
        }else if(strcmp(args[0], "quit") == 0)
        {
            char c;
            printf("Are you sure you want to exit? All files will be lost. Y/N\n");
            scanf("%c", &c);
            c = toupper(c);
            if(c == 'N')
            {
                printf("Returning to main menu\n");
            }else if(c == 'Y')
                quit();
        }else
            printf("Invalid selection: enter again or check # of arguments\n");
        
        //clear command line
        i = 0;
        memset(args, 0, sizeof(args));
        argCount = 0;
        
        //Get input from user again
        getInput(choice, MAX_CHOICE);
    }


}