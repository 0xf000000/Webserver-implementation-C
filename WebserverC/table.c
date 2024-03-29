//
//  table.c
//  WebserverC
//
//  Created by Leon Margale on 27.12.22.
//



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"
#include "list.h"
#define DEFAULTSIZE 128


// Datenstruktur die den Tisch eintrag hält


struct foreach_callback{
    void *arg;
    void (*f)(void*, void*);
};

void addEntrycount(struct hashtable* ht, int d  ){
    ht->num_entries +=d;
    ht->load = (float) ht->num_entries / ht->size;
}


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
    
    struct hashtable* newTable =  malloc(sizeof(*newTable));
    if(newTable == NULL){

        return NULL;
    }
    
    newTable->size = size;
    newTable->hashf = HASHFUNCTION;
    newTable->bucket = malloc( size * sizeof(struct list));
    newTable->num_entries = 0;
    newTable->load = 0;
    
    for(int i = 0; i < size; i++){
        
        
        newTable->bucket[i] =  *createList();
    }
    
    
    return newTable;
}

// we need to check first if the hashtable pointer or the data is null otherwise there is no reason to store it

void* putIntoTable(struct hashtable* table, void* data, char *key){
    
    if(table == NULL || data == NULL) return NULL;
    
    return putHashtableBin(table,key, strlen(key),data );
}

/*
 takes the key into binary form in order to hash it and then put it into our hashtable
 */
void* putHashtableBin( struct hashtable* table, void* key,int keysize, void* data){
    
    int index = table->hashf(key, keysize, table->size);
    
    printf("LOG: putHashtableBin() index that got put %i", index);
    struct list* list = &table->bucket[index];
    struct TableEntry* entry = malloc(sizeof(struct TableEntry* ));
    
    entry->key = key;
    entry->keySize = keysize;
    entry->data = data;
    entry->hashedKey=index;
    
    
    if(appendNode(list, entry) == NULL ){
        free(entry->key);
        free(entry);
    }
    
    
    
    return data;
}

void hashentryFree(void *ent, void *arg){
    (void)arg;
    
    free(ent);
}


void hashtableDestroy(struct hashtable* table){
    for(int i = 0; i < table->size; i++){
        struct list* list = &table->bucket[i];
        
        foreachNode(list, hashentryFree, NULL);
        
        destroyList(list);
        
    }
    
    free(table);
    
}

void* hashtableGETbinary( struct hashtable* table, void* key, int keylength){
    
    // here i think we have to transfer the funktionpointer
    int (*hashf)(void *data, int dataSize, int bucketCount) = table->hashf;
    int index = table->hashf(key, keylength, table->size);
    
    
    printf("LOG: this is the current Index my hashfunction provides %i", index);
    struct list* mylist = &table->bucket[index];
    
    struct TableEntry cmpent;
    cmpent.key = key;
    cmpent.keySize = keylength;
    
    struct TableEntry* ent = listFind(mylist, &cmpent, tablecompare);
    
    if(ent == NULL) {
        printf("LOG (DEBUG): entry is NULL");
        
        return NULL; }
    
    return ent->data;
    
    
}





void* hashtableGET(struct hashtable* table, char* key){
    // quick nullptr check
    if(table == NULL || key == NULL ){ return NULL;}
    
    
    void* value = hashtableGETbinary(table, key, strlen(key));
    
    return value;
    
    
}



int tablecompare(void *a, void *b){
    struct TableEntry *entA = a, *entB = b;
    
    
    int Sizedifference = entB->keySize - entA->keySize;
    printf("\n LOG: tablecompare() the size differens is %i\n", Sizedifference);
    
    
    if( strcmp(entB->key, entA->key) == 0 ){
        return 0;
    }
    
    
    
    if(Sizedifference){
        return Sizedifference;
    }
    
    
    return memcmp(entA->key, entB->key, entA->keySize);
}


void* hashtableDelete(struct hashtable *table, char* key){
    
    return hashtableDeleteBIN(table, key, strlen(key));
    
}


void* hashtableDeleteBIN(struct hashtable* table, void* key, int size){
    
    int index = table->hashf(key, size, table->size);
    
    struct list* mylist = &table->bucket[index];
    
    struct TableEntry myentry;
    myentry.key = key;
    myentry.keySize = size;
    
    
    struct TableEntry* entryData = listFind(mylist, &myentry,tablecompare);
    
    if(entryData == NULL){
        
        return NULL;
    }
    
    void* data = entryData->data;
    
    free(entryData);
    
    
    return data;
}


void hashtableForEach(struct hashtable* table, void (*f) (void *, void *), void *arg){
    
    struct foreach_callback payload;
    
    
    payload.f = f;
    payload.arg = arg;
    
    
    for (int i = 0; table -> size < i; i++ ){
        struct list* List = &table->bucket[i];
    
        foreachNode(List, payload.f, payload.arg);
    }
}

/**
 callback für die foreach function 
 */
void foreach_callback(void *vent , void *vpayload){
    
    struct TableEntry* tEntry = vent;
    struct foreach_callback *payload = vpayload;
    
    payload->f(tEntry->data, payload->arg);
}
    

