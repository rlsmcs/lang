#include "vector.h"
#include <stdlib.h>
void tokenVectorInit(struct TokenVector *vector){
    vector ->data =NULL;
    vector->size=0;
    vector->capacity=0;

}

//now push func which is dynamic also 

void tokenVectorPush(struct TokenVector *vector, struct Token token){
    if(vector->size==vector->capacity){
        size_t newCapacity;
        if(vector->capacity==0){
            newCapacity=8; // initial memory capacity cuz its 0 before
        }
        else{
            newCapacity= vector->capacity *2;
        }
        struct Token *newData=realloc(vector->data, newCapacity *sizeof(struct Token));
        if(newData==NULL){
            return;
        }
        vector->data=newData;
        vector->capacity=newCapacity;
    }
    vector->data[vector->size]=token;
    vector->size++;

}

void tokenVectorFree(struct TokenVector *vector){
    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;

}
