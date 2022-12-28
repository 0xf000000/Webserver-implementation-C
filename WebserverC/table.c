//
//  table.c
//  WebserverC
//
//  Created by Leon Margale on 27.12.22.
//


#include <stdio.h>
#include "table.h"
#define DEFAULTSIZE 128

struct TableEntry{
    void *key;
    int keySize;
    int hashedKey;
    void* data;
};

/*
 this hashfunction maps our data
 */
int hashfunction(void *data, int dataSize,int bucketCount){
    
    const int R  = 31;
    int h = 0;
    unsigned char *p = data;
    for(int i = 0;i < dataSize; i++){
        
        h = (R * h + p[i]) % bucketCount;
        
    }
    return h;
}

// creates a new Hashtable in heap  and returns a point to it
struct hashtable* createTable(int size , int (*HASHFUNCTION) (void*,int , int )){
    
    if(size < 1 ){
        size = DEFAULTSIZE;
    }
    
    if(HASHFUNCTION == NULL){
        HASHFUNCTION = hashfunction;
    }
    
    struct hashtable* newTable = malloc(sizeof(newTable));
    
    if(newTable == NULL){
        
        return NULL;
    }
    
    newTable->size = size;
    newTable->hashf = HASHFUNCTION;
    newTable->bucket = malloc( size * sizeof(struct list *));
    newTable->num_entries = 0;
    newTable->load = 0;
    
    
    return newTable;
}

void* putIntoTable(struct hashtable* table, void* data, char *key){
    
    if(table == NULL){
        return NULL;
    }
    
    int index = table->hashf(key,strlen(key), table->size);
    
    struct list* s = &table->bucket[index];
        
    
    return NULL;
}




