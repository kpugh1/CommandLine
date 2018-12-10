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
void systemFile(char*, char*);

//Global Variables
FILE *infile, *outfile, *readfile;

int main(int argc, char *argv[])
{
    //Variables
    char binCharacter[9];
    int binNum, decNum = 0, remainder, i = 0;
	
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
    outfile = fopen("middleman.txt", "w");
    
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
    
    fprintf(outfile, "%c", '\n');

//Cleans up in main.
fflush(stdout);
fclose(infile); fclose(outfile);
systemFile("middleman.txt", argv[2]);
}


void systemFile(char* file, char* direct)
{
    //Opens two FILES to the same translated output.
    infile = fopen(file, "r");      //infile is for getting the first word of each line.
    readfile = fopen(file, "r");    //readfile is for getting the whole line.

    //Variables
    char firstWord[10]; char line[50];
    char airlinecode[6]; char airlinefile[10];
    char allLines[250][50];
    int i = 0, size = 0;
    //airlinecode for the letters themselves, airlinefile for the filename.
    
    //Create directory for flight records using create
    //printf("%s\n", direct);
    char *dirargs[] = {"./create", "-d", direct, NULL};
    int status;
    
    pid_t pid;
    if((pid = fork()) == -1)
    {
        printf("Fork failed\n");
    }else if(pid == 0)
    {
        if(execvp(dirargs[0], dirargs) < 0)
            printf("Failed to create directory");
    }else
    {
        waitpid(pid, &status, 0);
    }

    //Populate array of lines
    while(!feof(infile))
    {
        fgets(allLines[i], 50, infile);
        size++;
        i++;
    }
    
    i = 0;
    
    //SORT THROUGH ARRAY HERE
    int spaceCount = 0, j = 0, k = 0;
    char lineDates[250][20];
    
    //Populate array of the dates and times of the line
    while(allLines[i][0] != '\0')
    {
        //populate the string inside the array
        while(allLines[i][j] != '\0')
        {
            //Do not put any chars into the string until 3 spaces have been found in the line
            if(spaceCount >= 3 && allLines[i][j] != '\n')
            {
                lineDates[i][k] = allLines[i][j];
                k++;
            }
            
            //If the character is whitespace, add 1 to spaceCount
            if(allLines[i][j] == ' ')
                spaceCount++;
                
            j++;
        }
        
        //null terminate
        lineDates[i][k] = '\0';
        
        i++;
        k = 0;
        j = 0;
        spaceCount = 0;
    }
    
    //Bubble sort through array
    char tempLine[50], tempDate[50];
    
    for(i = 0; i < (size - 1); i++)
    {
        for(j = 0; j < (size - i - 1); j++)
        {
            if(strcmp(lineDates[j], lineDates[j+1]) > 0)
            {
                strcpy(tempLine, allLines[j]);
                strcpy(tempDate, lineDates[j]);
                
                //Swap lines in original array
                strcpy(allLines[j], allLines[j+1]);
                strcpy(allLines[j+1], tempLine);
                
                //Swap lines in dates array
                strcpy(lineDates[j], lineDates[j+1]);
                strcpy(lineDates[j+1], tempDate);
            }
        }
    }
    
    //Traverse the array and create text files
    for(i = 1; i < size; i++)
    {
        char filepath[200];
        strcpy(filepath, direct);
        sscanf(allLines[i], "%s%*[^\n]", firstWord);
        
        for (j = 0; j < strlen(firstWord); j++)
        {
           
            if (firstWord[j] >= 65 && firstWord[j] <= 90)//!('0' <= firstWord[i] && '9' >= firstWord[i]))
            {
                airlinecode[j] = firstWord[j];
                airlinefile[j] = firstWord[j];
            }else
                airlinefile[j] = '\0';
        }
        //airlinefile[2]= '.'; airlinefile[3]= 't'; airlinefile[4]= 'x'; airlinefile[5]= 't'; airlinefile[6] = NULL;
        strcat(airlinefile, ".txt");

        //Create full filepath for the text file
        strcat(filepath, airlinefile);
        
        //Reset airlinefile to NULL
        airlinefile[0] = '\0';
        
        //Checks if a file already exists, if it does then the line is put into it
        if((outfile = fopen(filepath, "r")) != NULL)
        {
            outfile = fopen(filepath, "a+");
            fputs(allLines[i], outfile);
        }else //the file is created
        {
            char *fileargs[] = {"./create", "-f", filepath, NULL};
            if((pid = fork()) == -1)
                printf("Failed to fork\n");
            else if(pid == 0)
            {
                if(execvp(fileargs[0], fileargs) < 0)
                    printf("Failed to create file\n");
            }else
                waitpid(pid, &status, 0);
                
            //Insert line into newly created file
            outfile = fopen(filepath, "a+");
            fputs(allLines[i], outfile);
        }

        fclose(outfile);
    }
    
    //Clean up
    fflush(stdout);
    fclose(infile);
    fclose(readfile);
    remove(file);
}

    
    //exit(0);
    /*OLD CODE
    while (!feof(infile))
    {
        char filepath[200];
        strcpy(filepath, direct);
        fgets(line, 50, readfile);
        fscanf(infile, "%s%*[^\n]", firstWord);
        
        for (int i = 0; i < strlen(firstWord); i++)
        {
           
            if (firstWord[i] >= 65 && firstWord[i] <= 90)//!('0' <= firstWord[i] && '9' >= firstWord[i]))
            {
                airlinecode[i] = firstWord[i];
                airlinefile[i] = firstWord[i];
            }else
                airlinefile[i] = '\0';
        }
        //airlinefile[2]= '.'; airlinefile[3]= 't'; airlinefile[4]= 'x'; airlinefile[5]= 't'; airlinefile[6] = NULL;
        strcat(airlinefile, ".txt");

        //Create full filepath for the text file
        strcat(filepath, airlinefile);
        
        //Reset airlinefile to NULL
        airlinefile[0] = '\0';

        //If the file already exists, it appends to the file.
        if((outfile = fopen(filepath, "r")) != NULL)
        {
            outfile = fopen(filepath, "a+");
            fputs(line, outfile);
        }else
        {
            char *fileargs[] = {"./create", "-f", filepath, NULL};
            if((pid = fork()) == -1)
                printf("Failed to fork\n");
            else if(pid == 0)
            {
                if(execvp(fileargs[0], fileargs) < 0)
                    printf("Failed to create file\n");
            }else
                waitpid(pid, &status, 0);
                
            //Insert line into newly created file
            outfile = fopen(filepath, "a+");
            fputs(line, outfile);
            
        }

        //Rest of the function cleans up filesystem.
        fclose(outfile);
    }
    //Close files and remove middleman file

    fclose(infile);
    fclose(readfile);
    remove(file);
}*/
//gcc hello.c -lm -o test to compile