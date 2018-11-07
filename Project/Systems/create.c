/* Create.c: Has the ability to make a file, directory, hard links, or soft links.
 * 
 * main: checks what the flag is to hand it to another function.
 *                  
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
//#include "prototypes.h"

//Function prototypes
void createFile(char*);
void createDirPath(char*);
void createSymoblicLink(char*, char*);
void createHardLink(char*, char*);
void createSymoblicLink(char*, char*);

int main(int argc, char* argv[])
{
    //Check for right number of argument
    if(argc < 2)
    {
        fprintf(stderr, "Not enough Arguments\n");
        exit(1);
    }
    
    switch(argv[1][1])
    {
        case 'f':
        printf("Opening File %s...\n", argv[2]);
        createFile(argv[2]);
        break;
        
        case 'd':
        printf("Creating director...y\n");
        createDirPath(argv[2]);
        break;
        
        case 'h':
        printf("Creating hardLink...\n");
        createHardLink(argv[2], argv[3]);
        break;
        
        case 's':
        printf("Creating soft link...\n");
        createSymoblicLink(argv[2], argv[3]);
        break;
        
        default:
        fprintf(stderr, "Identifier not recognized\n");
        exit(1);
    }
    return 0;
}

//Creates a file with permissions of 0640
void createFile(char* filePath)
{
    //Variables
	FILE* file;
	mode_t mode = 0640;
	file = fopen(filePath, "w");
 
	if(file == NULL)
	{
		fprintf(stderr,"File cannot open\n");
		exit(1);
	}
	chmod(filePath, mode);
	printf("File %s opened.\n ", filePath); 
}

//Creates a directory with permissions of 0750
void createDirPath(char* dirpath)
{
    mode_t mode = 0750;
    if((mkdir(dirpath, mode)) == -1)
    {
        fprintf(stderr, "Directory cannot open\n");
        exit(1);
    }
    printf("Directory %s opened successfully.\n", dirpath);
}

//Creates a hard link to a file
void createHardLink(char* oldname, char* linkName)
{
    struct stat statbuf;
    if(stat(oldname,&statbuf) == -1)
    {
        fprintf(stderr,"File %s doesn't exist!\n", oldname);
        exit(1);
    }

    if(link(oldname,linkName) == -1)
    {
        fprintf(stderr, "Could not make a hard link.\n");
        exit(1);
    }
    printf("Successfully hard linked %s to %s.\n", linkName, oldname);
}

//Creates a soft link to a file
void createSymoblicLink(char* oldname, char* linkName)
{
    struct stat statbuf;
    if(stat(oldname, &statbuf) == -1)
    {
        fprintf(stderr,"%s does not exist!\n", oldname);
        exit(1);
    }
    
    if(symlink(oldname, linkName) == -1)
    {
        fprintf(stderr, "Could not make a symbolic link.\n");
        exit(1);
    }
    printf("Successfully created symbolic link from %s to %s.\n", linkName, oldname); 
}