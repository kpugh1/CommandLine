#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc , char* argv[]){
    //Parse a set of files
    //Create an inverted index, which maps each airport code
    //  found in the files to the subset of files that contain
    //  that code
    
    struct stat path;
    


    
    if(argc == 1){
        fprintf(stderr, "Not enough arguments\n");
    }
    else if(argc == 3){
        
    }

    if((stat(argv[1],&path) == 0) && S_ISDIR(path.st_mode)){
        printf("Is directory\n");
    }
    else{
        printf("Not a directory.\n");
    }


    



}