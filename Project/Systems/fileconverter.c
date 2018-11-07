/* Fileconverter: converts bin into separate airline text files.
 *
 * main: creates a translated txt file of the bin file.
 * systemfile: uses the translated txt file to create separated airline txt files
 *
 * Needs changing: Use create.c to make the files instead of the manual way.
 * Make systemfile: check to see if a line was already in the separated airline txt.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/wait.h>

//Function Prototypes
void systemFile(char*);

//Global Variables
FILE *infile, *outfile, *readfile;

main(int argc, char *argv[])
{
    //Variables
    char binCharacter[9];
    int binNum, decNum = 0, remainder, i = 0;

    /*
    printf("%s\n", argv[0]);
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    */
   
    //Open input file
    infile = fopen(argv[1], "r");

    //Checks if file exists and checks if it ends in .bin
    if(infile == NULL)
    {
        printf("Error: Cannot open input file\n");
        exit(0);
    }

    if (strcmp(&argv[1][strlen(argv[1]) - 4],".bin") != 0)
    {
        printf("Error: Incorrect input file type\n");
        exit(0);
    }

    //Create output file
    outfile = fopen(argv[2], "w");
    
    if(outfile == NULL)
    {
        printf("Error: Cannot open output file\n");
        exit(0);
    }

   //Translate binary characters in input file and output to output file
   while(fgets(binCharacter, sizeof(binCharacter), infile))
   {
       //Convert string to int
       binNum = atoi(binCharacter);

       //Convert binary number to decimal
       //This method was copied from
       //https://www.programiz.com/c-programming/examples/binary-decimal-convert
       while(binNum != 0)
       {
           remainder = binNum % 10;
           binNum /= 10;
           decNum += remainder * pow(2,i);
           i++;
       }

    //Print to output file
    fprintf(outfile, "%c", decNum);

    //Reset values for decimal conversion
    decNum = 0;
    i = 0;
    }
printf("Finished\n");

//Cleans up in main.
fflush(stdout);
fclose(infile); fclose(outfile);
systemFile(argv[2]);
}


void systemFile(char* file)
{
    //Opens two FILES to the same translated output.
    infile = fopen(file, "r");      //infile is for getting the first word of each line.
    readfile = fopen(file, "r");    //readfile is for getting the whole line.

    //Variables
    char firstWord[10]; char line[50];
    char airlinecode[2]; char airlinefile[6];
    //airlinecode for the letters themselves, airlinefile for the filename.

    airlinefile[2]= '.'; airlinefile[3]= 't'; airlinefile[4]= 'x'; airlinefile[5]= 't'; airlinefile[6] = NULL;
    
    //Create directory for flight records using create
    char *dirargs[] = {"./create", "-d", "Flight Records", NULL};
    int status;
    
    pid_t pid;
    if((pid = fork()) == -1)
    {
        printf("Fork failed\n");
    }else if(pid == 0)
    {
        if(execvp(dirargs[0], dirargs) < 0)
            printf("Failed to create directory");
    }
    //printf("%d\n", pid);
    waitpid(-1, &status, WUNTRACED);

    //Traversing the newly translated file
    while (!feof(infile))
    {
        char *filepath[] = "/Flight Records/";
        fgets(line, 50, readfile);
        fscanf(infile, "%s%*[^\n]", firstWord);
        //printf("first word read is: %s\n", line);
        //printf("first word read is: %s\n", firstWord);
        //printf("%s", airlinefile);

        for (int i = 0; i < strlen(firstWord); i++)
        {
            if (firstWord[i] >= 65 && firstWord[i] <= 90)//!('0' <= firstWord[i] && '9' >= firstWord[i]))
            {
            airlinecode[i] = firstWord[i];
            airlinefile[i] = firstWord[i];
            }
        }
        airlinefile[2]= '.'; airlinefile[3]= 't'; airlinefile[4]= 'x'; airlinefile[5]= 't'; airlinefile[6] = NULL;

        strcat(filepath, airlinefile);
        printf("%s\n", filepath);

        //If the file already exists, it appends to the file.
        if((outfile = fopen(filepath, "a+")) != NULL)
        {
            //fputs(line, outfile);
        }

        //If the file doesn't exist, it creates it.
        else
        {
            //WORK IN PROGRESS
            //TRYING TO CREATE FILE INSIDE OF FLIGHT RECORDS DIRECTORY
            char *fileargs[] = {"./create", "-f", filepath, NULL};
            if(pid = fork() == -1)
                printf("Failed to fork\n");
            else if(pid == 0)
            {
                if(execvp(fileargs[0], fileargs) < 0)
                    printf("Failed to create file\n");
            }
            //fputs(line, filepath);
        }

        //Rest of the function cleans up filesystem.
    fclose(outfile);
    }
fclose(infile);
fclose(readfile);
}

//gcc hello.c -lm -o test to compile
