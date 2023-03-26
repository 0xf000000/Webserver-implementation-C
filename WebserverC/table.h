//
//  table.h
//  WebserverC
//
//  Created by Leon Margale on 27.12.22.
//

#ifndef table_h
#define table_h
/**
 cool thing on this hashtable implementation is that you can choose your own hashfunction implementation :-)
 */
struct hashtable{
    int size;
    int num_entries;
    int load;
    struct list* bucket;
    int (*hashf)(void *data, int dataSize, int bucketCount);
};
struct hashtable* createTable(int size , int (*HASHFUNCTION) (void*,int , int ));
extern void hashtableForEach(struct hashtable* ht, void (*f) (void *, void *), void *arg); 
extern int hashfunction(void *data, int dataSize,int bucketCount);
extern void* putHashtableBin( struct hashtable* table, void* key,int keysize, void* data);
extern void* putIntoTable(struct hashtable* table, void* data, char *key);
extern void hashentryFree(void *ent, void *arg);
extern void hashtableDestroy(struct hashtable* table);
extern void* hashtablGETbinary( struct hashtable* table, void* key, int keylength);
extern int tablecompare(void *a, void *b);
extern void addEntrycount(struct hashtable* ht, int d  );
extern void * hashtableDelete(struct hashtable *table, char* key);
extern void* hashtableDeleteBIN(struct hashtable* table, void* key, int size);
#endif /* table_h */
