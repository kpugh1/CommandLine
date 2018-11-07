#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_CHOICE 50
#define MAX_ARGS 4
#define MAX_ARG_SIZE 20

pid_t pid;
int status;
char *args[MAX_ARGS][MAX_ARG_SIZE];

int main(int argc, char *argv[])
{
    //variables
    char *choice = malloc(MAX_CHOICE);
    char *token;
    int i = 0;
    
    memset(args, 0, sizeof(args));
    
    //prompt user for their input
    printf("Please enter a selection: ");
    fgets(choice, MAX_CHOICE, stdin);
    for(int i = 0; i<strlen(choice); i++)
    {
        if(choice[i] == '\n')
        choice[i] = '\0';
    }
    
    i=0;
    
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
        }

        i = 0;
        
        //Perform commands based on user input
        if(strcmp(args[0], "fileconverter") == 0)
        {
            fileconverter();
            wait(&status);
        }else if(strcmp(args[0], "create") == 0)
        {
            create();
            wait(&status);
        }else if(strcmp(args[0], "quit") == 0)
        {
            quit();
        }else
            printf("Invalid selection\n");
        
        //clear command line
        i = 0;
        memset(args, 0, sizeof(args));
        
        //prompt user for their input
        printf("Please enter a selection: ");
        fgets(choice, MAX_CHOICE, stdin);
        for(int i = 0; i<strlen(choice); i++)
        {
            if(choice[i] == '\n')
            choice[i] = '\0';
        }
    }


}