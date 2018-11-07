/*Artem Yeremeyev
  This function translates binary to text, then outputs it into a file
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void systemFile(char*);

FILE *infile, *outfile;

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
        printf("Error: Cannot open file\n");
        exit(0);
    }
    
    //Create output file
    outfile = fopen(argv[2], "w");
    
    
    /* TODO: Do we even need this? The file will create a new one if it doesn't exist.
    if(outfile == NULL)
    {
        printf("Error: Cannot open file\n");
        exit(0);
    }
    */
    
    
    /* TODO: Should we make sure the middle file is always a text file so when it reads it to separate for airlines?
    // Makes sure the middleman file is a text so it works properly.
    if (strcmp(&argv[2][strlen(argv[2]) - 4],".txt") != 0)
    {
        printf("Error: Incorrect input file type");
        return 0;
    }
    */
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
    fflush(stdout); fclose(infile); fclose(outfile);
    
    
    systemFile(argv[2]);
}

void systemFile(char* file){
    infile = fopen(file, "r");
    
    char firstWord[10];
    //char line[50];
    char airlinecode[2];
    char airlinefile[6];
    airlinefile[2]= '.'; airlinefile[3]= 't'; airlinefile[4]= 'x'; airlinefile[5]= 't';
    while (!feof(infile)) {
        
        fscanf(infile,"%s%*[^\n]",firstWord);
        printf("first word read is: %s\n", firstWord);
        for(int i = 0; i < strlen(firstWord); i++)
        {
            if (!('0' <= firstWord[i] && '9' >= firstWord[i])){
                airlinecode[i] = firstWord[i];
                airlinefile[i] = firstWord[i];
            }
            
        }
        /* TODO: The above is opening the output file from main, reading the first word and 
        gettin rid of the numbers from it. This is assuming all airport are 2 letters 
        (This will need to be fixed since there is an example of F9612, but just for simplicity sake, 
        we'll have it like for now)
        We can print the 
        Whats left to do for fileconvert.c is:
        * Check if theres already a file for a airlinecode by checking if fopen is null.
            * Add the line to the existing airlinefile. 
        * If it doesn't exist, create the file then add the line to it.
        */        
        outfile = fopen("parsedtext.txt", "w");
        fprintf(outfile, "%s\n", airlinecode);
        fclose(outfile);
        
        outfile = fopen(airlinefile, "a");
        //fscanf(infile,"%s", line);
        //printf("hi guys %s\n", line);
        //fprintf(outfile, "%s\n", line);
        
    }
    fclose(infile);
    fclose(outfile);
}

//gcc hello.c -lm -o test to compile