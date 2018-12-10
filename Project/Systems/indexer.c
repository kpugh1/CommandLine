#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "airline.c"

//#include "interfaceFunctions.c"

//Globals
AirlineMap* map = NULL;

int readFiles(const char* , const struct stat* , int );
void printMap(AirlineMap*);

int main(int argc , char* argv[]){
    //Parse a set of files
    //Create an inverted index, which maps each airport code
    //  found in the files to the subset of files that contain
    //  that code
    DIR* dir;
    struct dirent* d;
    struct stat path;
    char* directory;
    char* indexerFile;
  //  FILE *fp;


    if(argc == 1){

        fprintf(stderr, "Not enough arguments\n");
    }
    else if(argc == 2){
        directory = argv[1];
        indexerFile = "invind.txt";
    }
    else if(argc == 3){
        indexerFile = argv[1];
        directory = argv[2];

    }

    if((dir= opendir(directory)) == NULL){
        fprintf(stderr,"Directory can not be opened.");

    }

    while((d = readdir(dir)) != NULL){
       
        if(d->d_type == DT_REG){

            printf("This is a file name %s\n", d->d_name);
            FILE* file;
            char* filename = d->d_name;
            if((file = fopen(filename,"r+")) == NULL){
                printf("Can't be opened.\n");
            }
            else{
                printf("File opened: %s",filename);
            }
           // char* url = "/home/k-dizzle/workspace/CommandLine/Project/Systems/";
            //char *path = strcat(url,d->d_name);
               
            //printf("path: %s",path);   
           // FILE* fp = fopen(path, "rw");
    
            //char airportArr[4];
            //char airportDep[4];
            //if(fp == NULL){
              //  fprintf(stderr, " File can not open\n");
               // return 1;
                //fclose(fp);
            //}
            /*
            while(fscanf(fp,"%*s %3s %3s %*s %*s\n",airportArr,airportDep) != EOF){
            //fscanf(fp,"%*s %3s %3s %*s %*s\n",airportArr,airportDep);
            AirlineMap* air;
            FrequencyList* f;
            if((air = findAirline(map,airportArr)) == NULL){
                printf("This arr string ends. %s\n",airportArr);
               
                f = createList(d->d_name,1);
                air = createMap(airportArr,f);
                addToMap(&map,air);
                
            }
            else{
                updateFreq(map, airportArr,d->d_name);
                printf("%s is updated in %s\n", airportArr, d->d_name);
            } 
            
            if((air = findAirline(map, airportDep)) == NULL){

               f = createList((char*)d->d_name, 1);
                air = createMap(airportDep,f);
                addToMap(&map,air);
            }
            else{
                updateFreq(map,airportDep,(char*)d->d_name);
            }

           //printf("arr = %s  and dep = %s\n", airportArr,airportDep);
            printf("%s ",map->airCode);
           
           }
            printMap(map);
            printf("\n");
            */
           // fclose(fp);
        }
    }
    
    closedir(dir);
    
    
    
    
    
    
    
    /*
    if((stat(directory,&path) != 0) || !(S_ISDIR(path.st_mode))){
        fprintf(stderr,"Directory cannot open\n");
		exit(1);
    }
    
    ftw(directory, readFiles, 1);
   */
   while(map != NULL){
       printf("%s->", map->airCode);
       map = map->next;
   }
   
   // printMap(map);

    printf("After map prints.\n");
/*
    strcpy((char*)args[1],"-f");
    strcpy((char*)args[2],indexerFile);
    printf("%s",(char*)args[3]);
    //strcpy((char*)args[3],NULL);
    create();
    mode_t mode = 0640;
	file = fopen(filePath, "w");

	if(file == NULL)
	{
		fprintf(stderr,"File cannot open\n");
		exit(1);
	}
	chmod(filePath, mode);
	printf("File %s opened.\n", filePath);
    
*/

        
    FILE* file;

    mode_t mode = 0640;
    if((file = fopen(indexerFile,"w")) == NULL){
        fprintf(stderr,"File cannot open\n");
		exit(1);
    }
    chmod(indexerFile,mode);

  
    
    fclose(file);
    
   

   return 0;

}

int readFiles(const char* fname, const struct stat* status, int type){

    switch(type){
        case FTW_D:
            printf("Directory name %s\n", fname);
            break;
        case FTW_F:
            printf("File Name %s\n", fname);
            FILE *fp = fopen(fname, "r");
    
            char airportArr[4];
            char airportDep[4];
            if(fp == NULL){
                fprintf(stderr, " File can not open.");
            }

           while(fscanf(fp,"%*s %3s %3s %*s %*s\n",airportArr,airportDep) != EOF){
            //fscanf(fp,"%*s %3s %3s %*s %*s\n",airportArr,airportDep);
            AirlineMap* air;
            FrequencyList* f;
            if((air = findAirline(map,airportArr)) == NULL){
                printf("This arr string ends. %s\n",airportArr);
                f = createList(fname,1);
                air = createMap(airportArr,f);
                addToMap(&map,air);
                
            }
            else{
                updateFreq(map, airportArr,fname);
                printf("%s is updated in %s\n", airportArr, fname);
            } 
            
            if((air = findAirline(map, airportDep)) == NULL){

               f = createList((char*)fname, 1);
                air = createMap(airportDep,f);
                addToMap(&map,air);
            }
            else{
                updateFreq(map,airportDep,(char*)fname);
            }

           //printf("arr = %s  and dep = %s\n", airportArr,airportDep);
            printf("%s ",map->airCode);
           
           }
            printMap(map);
            printf("\n");
            fclose(fp);
            break;
        case FTW_SL:
            return 0;
            break;
        case FTW_DNR:
        case FTW_NS:
            printf("Not readable.\n");
            return 0;
            break;
        }
        return 0;
}

void printMap(AirlineMap* map){
    while(map != NULL){
        printf("%s->",map->airCode);

        map = map->next;
    }
}

/*
void printMap(AirlineMap* map, FILE* fp){
    AirlineMap* trav = map;
   // char* out;
    //char* code[4];
    while(trav != NULL){
        //code = trav->airCode
        //fprintf(fp,"%s ", trav->airCode);
        //fputs(strcat(trav->airCode, " "),fp);

        printf("%s->", trav->airCode);
       
       /*
        FrequencyList* list = trav->list;
        while(list != NULL){
        
            //fprintf(fp, "%s %d ",list->fileName,list->freqency);
            //strcat(code, fileInfo);
           // strcat(code, list->fileName);
            //strcat(code, " ");
            //strcat(code, list->freqency));
           // strcat(code," ");
            list = list->next;
        }
        */
        //strcat(code,"\n");
     //   trav = trav->next;
        //printf("\n");
        //fprintf(fp,"\n");
        //strcat(out,code);
   // }

    //fprintf(fp,"\n");
    //strcat(code, "\0");
//}
