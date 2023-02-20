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






#endif /* cache_h */
