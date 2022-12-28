//
//  table.h
//  WebserverC
//
//  Created by Leon Margale on 27.12.22.
//

#ifndef table_h
#define table_h
struct hashtable{
    int size;
    int num_entries;
    int load;
    struct list* bucket;
    int (*hashf)(void *data, int dataSize, int bucketCount);
};
extern int hashfunction(void *data, int dataSize,int bucketCount);

#endif /* table_h */
