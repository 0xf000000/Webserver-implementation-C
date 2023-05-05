//
//  cache.c
//  WebserverC
//
//  Created by Leon Margale on 21.02.23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "cache.h"
#include "file.h"

struct cacheEntry *dllist_remove_tail(struct cache *cache){
    struct cacheEntry *oldtail = cache->tail;

        cache->tail = oldtail->prev;
        cache->tail->next = NULL;

        cache->curSize--;

        return oldtail;
}



// should allocate a cache entry
struct cacheEntry* alloc_Entry(char *path, char *contentType, void *content,  int contentLength){
    
    struct cacheEntry* entry = malloc(sizeof(struct cacheEntry));
    entry->path = path;
    entry->content = content;
    entry->content_type=contentType;
    entry->content_length = contentLength;
    
    
    return entry;
}

void InsertHeadDoubleLinkedList(struct cache *cache, struct cacheEntry *ce){
    if(cache->head == NULL){
        cache->head = cache->tail = ce;
        ce->prev = ce->next = NULL;
    } else{
        
        cache->head->prev=ce;
        ce->next= cache->head;
        ce->prev = NULL;
        cache->head = ce;
    }
    
}

struct cache *cacheCreate(int max_size, int hashsize)
{
    struct cache* cache = malloc(sizeof(struct cache));
    
    int finalHashsize = hashsize;
    
    cache->maxSize = max_size;
    cache->curSize = 0;
    
    if(finalHashsize <= 1 ){ finalHashsize = 5; }
    
    cache->index = createTable(finalHashsize,&hashfunction);
    cache->head = NULL;
    cache->tail = NULL;
    
    
    return cache;
}

void cache_free(struct cache *cache){
    struct cacheEntry* currentEntry = cache->head;
    hashtableDestroy(cache->index);
    
    while(currentEntry != NULL){
        struct cacheEntry* nextEntry = currentEntry->next;
        free_entry(currentEntry);
        currentEntry = nextEntry;
    }
    
    free(cache);
}

void  free_entry(struct cacheEntry *entry)
{
    
    if(entry == NULL){
        return;
    }
    
    free(entry->content);
    free(entry->content_type);
    free(entry->path);
    free(entry);
   
}


void cachePut(struct cache *cache, char *path, char *content_type, void *content, int content_length){
    if(cache == NULL){
        printf(" (-) ERROR: cache struct ist NULL");
        return;
    }
    if(cache->curSize +1  > cache->maxSize){
        printf(" (-) ERROR: the cache has no space for another entry");
        return;
    }
    
    
    struct cacheEntry* entry = alloc_Entry(path, content_type, content, content_length);
    
    InsertHeadDoubleLinkedList(cache, entry);
    
    putIntoTable(cache->index, entry, path);
    cache->curSize++;
}



// what the fuck is that?
struct cacheEntry* cacheGet(struct cache* cache, char* path){
    
    
    // always checkups for nullptr
    if( cache == NULL){
        return NULL;
    }

    struct cacheEntry* entry = hashtableGET(cache->index, path);
    
    if(entry == NULL){
        return NULL;
    }
    
    
    
    //DEBUG
    printf("LOG: an Entry will be returned that exists"); 
    
    
    return entry;
}
