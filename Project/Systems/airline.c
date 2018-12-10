#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Globals


//Structs
typedef struct freqlist{
    const char* fileName;
    int freqency;
    struct freqlist* next;
}FrequencyList;

typedef struct airlinemap {
    char* airCode;
    FrequencyList* list;
    struct airlinemap* next;
}AirlineMap;

//Prototypes
void addToMap(AirlineMap**, AirlineMap*);
void addFreq(FrequencyList*, const char*, int);
void updateFreq(AirlineMap*, char*, const char*);
AirlineMap* findAirline(AirlineMap*, char*);
AirlineMap* createMap(char*, FrequencyList*);
FrequencyList* createList(const char*, int);
void freeMap(AirlineMap*);
 

void freeMap(AirlineMap* map){
    AirlineMap* trav;
    trav = map;
    while(map != NULL){
        FrequencyList* fl = map->list;
        FrequencyList* curr = fl;
        while(fl->next != NULL){
            fl = fl->next;
        }
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

FrequencyList* createList(const char* fname,int freq){
    FrequencyList* fl = (FrequencyList*)malloc(sizeof(FrequencyList));
    fl->fileName = fname;
    fl->freqency = freq;
    fl->next = NULL;

    return fl;
}

void addFreq(FrequencyList* list, const char* fName, int freq){
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

void updateFreq(AirlineMap* head, char* airportCode, const char* fName){
   AirlineMap* airMap = findAirline(head, airportCode);

    if(airMap == NULL){
        
    }
    else{
        FrequencyList* list = airMap->list;
        int found = 0;
        while(list != NULL && found <= 0){
            if(strcmp(list->fileName, fName) == 0){
                list->freqency = list->freqency + 1;
                found++;

               // printf("New List Frequency %d\n", list->freqency);
            }
            list = list->next;
        }

        if(found == 0){
            FrequencyList* newFreq = createList(fName, 1);
            addFreq(list,fName,1);
        }
    }

}

void addToMap(AirlineMap** map, AirlineMap* newAirline){
  
    AirlineMap* curr;
    if(*map == NULL || (strcmp((*map)->airCode, newAirline->airCode) > 0)){
       // printf("m p is null");
        newAirline->next = *map;
        *map =  newAirline;
    }
    else{
        AirlineMap* curr = *map;
        while((strcmp(curr->airCode, newAirline->airCode) > 0)  && curr != NULL){
           printf("%s\n",curr->airCode);
           curr = curr->next;
        } 
        newAirline->next = curr->next;
        curr->next = newAirline;
    }

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

/*
int main(){
    AirlineMap* mapHead = NULL;
    FrequencyList* list = (FrequencyList*)malloc(sizeof(FrequencyList));
    FrequencyList* curr;
    list->fileName = "one.txt";
    list->freqency = 0;
    list->next = (FrequencyList*)malloc(sizeof(FrequencyList));
    curr = list->next;

    curr->fileName = "two.txt";
    curr->freqency = 0;
    curr->next = (FrequencyList*)malloc(sizeof(FrequencyList));
    curr = curr->next;

    curr->fileName = "three.txt";
    curr->freqency = 0;
    curr->next = (FrequencyList*)malloc(sizeof(FrequencyList));
    curr = curr->next;
    
    curr->fileName = "four.txt";
    curr->freqency = 0;
    curr->next = NULL;


    char* airlines[] = {"Ken","NFW","HUM","JFK","AAF"};

   // AirlineMap* map;
    for(int i = 0; i< 5;i++){
       AirlineMap* map = createMap(airlines[i], list);
        addToMap(&mapHead,map);
    }

    AirlineMap* map1 = createMap("Ken",list);
    AirlineMap* map2 = createMap("NFW", list);
    AirlineMap* map3 = createMap("HUM",list );
    AirlineMap* map4 = createMap("JFK",list);
    AirlineMap* map5 = createMap("AAF",list);

    addToMap(&mapHead, map1);
    addToMap(&mapHead, map2);
    addToMap(&mapHead, map3);
    addToMap(&mapHead, map4);
    addToMap(&mapHead, map5);

    updateFreq(mapHead,"HUM","three.txt");
    updateFreq(mapHead,"JFK","three.txt");
    updateFreq(mapHead,"HUM","two.txt");

    //printMap(mapHead);
    //mapHead = (AirlineMap*) malloc(sizeof(AirlineMap));
    
    //mapHead->airCode = "JFK";
    //mapHead->list = NULL;
    
   // addToMap(mapHead, "KEN", NULL);
    //addToMap(mapHead, "NFW", NULL);
    //addToMap(mapHead, "HUM", NULL);
    //addToMap(mapHead, "YOU", NULL);

    AirlineMap* temp = mapHead;

    while(temp != NULL){
        printf("%s->", temp->airCode);
        temp = temp->next;
    }

    printf("\n");
      
    
   // free(flist);
    free(mapHead);

    return 0;
 }
*/

