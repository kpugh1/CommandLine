#include <stdio.h>
#include <string.h>

#define MAX_CHOICE 50

//Function to get input from the user
void getInput(char* choice, int max)
{
    //prompt user for their input
    printf("Please enter a selection: ");
    fgets(choice, max, stdin);
    for(int i = 0; i<strlen(choice); i++)
    {
        if(choice[i] == '\n')
        choice[i] = '\0';
    }
}

//Function to read input from the script file
char* getLine(FILE *stream)
{
	char* line = malloc(MAX_CHOICE);
	
	fgets(line, MAX_CHOICE, stream);
    for(int i = 0; i<strlen(line); i++)
    {
        if(line[i] == '\n')
        line[i] = '\0';
  	}
  	
  	return line;
}