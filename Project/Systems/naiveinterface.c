#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "interfaceFunctions.c"
#include "input.c"

#define MAX_CHOICE 50
#define MAX_ARGS 4
#define MAX_ARG_SIZE 20

pid_t pid;
int status;
int directCount;
int fileCount; 
int linkCount;
char *args[MAX_ARGS][MAX_ARG_SIZE];
char outdirectory[50][200];
char currFiles[50][200];
char currLinks[50][200];

int main(int argc, char *argv[])
{
	//variables for script file
    FILE* scriptfile;
    
    //variables
    char *choice = malloc(MAX_CHOICE);
    char *token;
    int i = 0, argCount = 0;
    directCount = 0;
    fileCount = 0;
    linkCount = 0;
    
    //set arguments to 0
    memset(args, 0, sizeof(args));

	//Open script file if there is one
	if(argc == 2)
	{
		if((scriptfile = fopen(argv[1], "r")) == NULL)
			printf("Could not open script file; switching to user input\n");
	}
	
	//if script file exists, read through it
	if(scriptfile !=NULL)
	{
		//read through script file until end of line and execute commands
		while(!feof(scriptfile))
		{
    		//read line from file	
    		strcpy(choice, getLine(scriptfile));
    		printf("%s\n", choice);
    		
    		//separate the command into argument array using strtok()
        	token = strtok(choice, " ");
	        while(token != NULL && i < MAX_ARGS)
	        {
				//printf("The token is: %s\n", token);
	            strcpy((char*)args[i], token);
 	            token = strtok(NULL, " ");
				i++;
				argCount++;
 	       	}
 	       	
    		//quit once quit command is reached, no need for user Y/N
    		if(strcmp((char*)args[0], "quit") == 0)
    			quit();
    			
    		//Execute command
    		chooseFunction(argCount);
    		
    		//clear command line and other specifics
        	i = 0;
        	memset(args, 0, sizeof(args));
        	argCount = 0;
        	choice[0] = '\0';
		}
	}

	//empty selection
	choice[0] = '\0';
	//get input from the user
    getInput(choice, MAX_CHOICE);
    
    //loop until user quits out of shell
    while(1)
    {
    
        //separate input into arg array using strtok()
        token = strtok(choice, " ");
        while(token != NULL && i < MAX_ARGS)
        {
            //printf("The token is: %s\n", token);
            strcpy((char*)args[i], token);
            token = strtok(NULL, " ");
            i++;
            argCount++;
        }
        
        //Execute the command based on user input
        chooseFunction(argCount);
        
        //clear command line and other specifics
        i = 0;
        memset(args, 0, sizeof(args));
        argCount = 0;
        choice[0] = '\0';
        
        //Get input from user again
        getInput(choice, MAX_CHOICE);
    }


}