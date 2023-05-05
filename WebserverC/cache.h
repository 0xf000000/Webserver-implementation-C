//
//  cache.h
//  WebserverC
//
//  Created by Leon Margale on 21.02.23.
//

#ifndef cache_h
#define cache_h

#include <stdio.h>
struct cacheEntry {
    char *path;
    char *content_type;
    int content_length;
    void *content;
    
    
    struct cacheEntry *prev, *next;
};


struct cache{
    struct hashtable *index;
    struct cacheEntry *head, *tail;
    int maxSize;
    int curSize;
};

extern struct cacheEntry *alloc_Entry(char *path, char *contentType, void *content,  int contentLength); 
extern void  free_entry (struct cacheEntry *entry);
extern struct cache* cacheCreate(int max_size, int hashSize);
extern void cache_free(struct cache *cache);
extern void cachePut(struct cache *cache, char *path, char *content_type, void *content, int content_length);
extern struct cacheEntry *cacheGet(struct cache *cache, char *path);
extern struct cacheEntry *dllist_remove_tail(struct cache *cache);

#endif /* cache_h */
