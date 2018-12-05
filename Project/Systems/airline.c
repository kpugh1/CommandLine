#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Globals


//Structs
typedef struct freqlist{
    char* fileName;
    int freqency;
    struct freqlist* next;
}FrequencyList;

typedef struct airlinemap {
    char* airCode;
    FrequencyList* list;
    struct airlinemap* next;
}AirlineMap;

//Prototypes
void addToMap(AirlineMap*, char*, FrequencyList*);
void updateFreq(FrequencyList*, char*, int);
AirlineMap* findAirline(AirlineMap*, char*);
AirlineMap* createMap(char*, FrequencyList*);
FrequencyList* createList(char*, int);
void freeMap(AirlineMap*);
 
//Definitions
void freeMap(AirlineMap* map){
    AirlineMap* trav;

    while(map != NULL){
        trav = map;
        map = map->next;
        
    }
}

AirlineMap* createMap(char* code, FrequencyList* nlist){
    AirlineMap* newMap = (AirlineMap*)malloc(sizeof(AirlineMap));
    newMap->airCode = code;
    newMap->list = nlist;
    newMap->next = NULL;

    return newMap;
}
FrequencyList* createList(char* fname,int freq){
    FrequencyList* fl = (FrequencyList*)malloc(sizeof(FrequencyList));
    fl->fileName = fname;
    fl->freqency = freq;
    fl->next = NULL;

    return fl;
}

void updateFreq(FrequencyList* list, char* fName, int freq){
    if(list == NULL){
        list = createList(fName, freq);
    }
    else{
        FrequencyList* newfreq = createList(fName, freq);
        FrequencyList* curr;
        while((freq >= list->freqency) && (list != NULL)){
            curr = list;
            list = list->next;
        }
        curr->next = newfreq;
        newfreq->next = list;
    }
}

void addToMap(AirlineMap* map, char* code, FrequencyList* flist){
   AirlineMap* trav = map;
   //AirlineMap* newMap = createMap(code, list);
    if(map == NULL){
        printf("map is null");
        //map = (AirlineMap*)malloc(sizeof(AirlineMap)); 
        map->airCode = code;
        map->list = flist;
    }/*
    else{
       AirlineMap* curr;
       // = (AirlineMap*)malloc(sizeof(AirlineMap)); 
       while((strcmp(trav->airCode, code) > 0)  && trav != NULL){
           curr = trav;
           printf("%s\n",trav->airCode);
           trav = trav->next;
       } 
       curr->next = newMap;
       newMap->next = trav;
    }
    */
}

AirlineMap* findAirline(AirlineMap* map, char* code){
    if(map == NULL){
        return NULL;
    }
    AirlineMap* trav = map;

    while(trav->next != NULL){
        if(strcmp(trav->airCode, code)== 0){
            return trav;
        } 
        trav = trav->next;
    }

    return NULL;

}


int main(){
    AirlineMap* mapHead;
    FrequencyList* flist;

    flist = (FrequencyList*)malloc(sizeof(FrequencyList));
   // mapHead = (AirlineMap*) malloc(sizeof(AirlineMap));
    
   // mapHead->airCode = "JFK";
   // mapHead->list = NULL;

    addToMap(mapHead, "KEN", flist);

    printf("%s\n", mapHead->airCode);
    //addToMap(mapHead, "NFW", NULL);
    //addToMap(mapHead, "HUM",NULL);
    //addToMap(mapHead, "YOU",NULL);

//printf("%d\n",compCode("AAM","AAA"));
 //  while(mapHead != NULL){
   //    printf("%s->", mapHead->airCode);
     //  mapHead = mapHead->next;
  // }
    

    return 0;
 }

