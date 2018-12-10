#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "interfaceFunctions.c"

#include "interfaceFunctions.c"
#include "input.c"

#define MAX_CHOICE 50
#define MAX_ARGS 4
#define MAX_ARG_SIZE 20

pid_t pid;
int status;
<<<<<<< HEAD
int directCount;
int fileCount; 
int linkCount;
char *args[MAX_ARGS][MAX_ARG_SIZE];
char outdirectory[50][200];
char currFiles[50][200];
char currLinks[50][200];
=======
int directCount, fileCount;
char *args[MAX_ARGS][MAX_ARG_SIZE];
char outdirectory[50][200];
char currFiles[50][200];
>>>>>>> 98502c455bae7a85324479723a5068c130ae851d

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
<<<<<<< HEAD
    linkCount = 0;
=======
>>>>>>> 98502c455bae7a85324479723a5068c130ae851d
    
    //set arguments to 0
    memset(args, 0, sizeof(args));

<<<<<<< HEAD
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
=======
>>>>>>> 98502c455bae7a85324479723a5068c130ae851d
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
        
<<<<<<< HEAD
        //Execute the command based on user input
        chooseFunction(argCount);
=======
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
>>>>>>> 98502c455bae7a85324479723a5068c130ae851d
        
        //clear command line and other specifics
        i = 0;
        memset(args, 0, sizeof(args));
        argCount = 0;
<<<<<<< HEAD
        choice[0] = '\0';
=======
>>>>>>> 98502c455bae7a85324479723a5068c130ae851d
        
        //Get input from user again
        getInput(choice, MAX_CHOICE);
    }


}