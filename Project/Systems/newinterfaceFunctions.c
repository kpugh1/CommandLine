#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX_ARGS 4
#define MAX_ARG_SIZE 20

//Structs
typedef struct freqlist{
    char* fileName;
    int freqency;
    struct freqlist* next;
}FrequencyList;

typedef struct airlinemap {
    char* airCode;
    FrequencyList* list;
}AirlineMap;


//Globals
extern pid_t pid;
extern int status;
extern char *args[MAX_ARGS][MAX_ARG_SIZE];

//Prototypes
void fileconverter();
void quit();
void addToMap(AirlineMap*, char*, FrequencyList);
void updateMap(AirlineMap*, char*, int);


void addToMap(AirlineMap* map, char* code, FrequencyList){
    if()
}

//Function to execute fileconverter
void fileconverter()
{
    printf("Starting file converter command\n");
    char *argv[] = {"./fileconverter", args[1], args[2], NULL};
    /*
    printf("%s\n", argv[0]);
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    */
    if((pid = fork()) < 0)
    {
        printf("Could not open fileconverter\n");
        exit(0);
    }else if(pid == 0)
    {
        if (execvp(argv[0], argv) < 0)
            printf("Failed to execute fileconverter command\n");           
    }
}

//Function to execute create
void create()
{
    printf("Starting create command\n");
    char *argv[] = {"./create", args[1], args[2], args[3], NULL};
    
    if((pid = fork()) < 0)
    {
        printf("Could not open create");
    }else if(pid == 0)
    {
        if(execvp(argv[0], argv) < 0)
            printf("Failed to execute create command\n");
    }
}

//Quit Program
//NOT YET COMPLETE
void quit()
{
    printf("Exiting program\n");
    exit(0);
}


