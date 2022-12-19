//
//  File.c
//  WebserverC
//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"


/*
 loads file data into our memory and should return a pointer
 TODO: this method is also way to long
 */

struct file_data* loadFile(char *filename){
    char *buffer, *p;
    struct stat buf;
    int bytes_remaining, bytes_read, total_bytes = 0;
    // get the File Size
    if(stat(filename, &buf) ==-1){
        
        return NULL;
    }
    
    //check if its a regular File
    if(!(buf.st_mode & S_IFREG)){
        return NULL;
    }
    
    FILE *fp = fopen(filename, "rb");
    
    // check if fp is nullptr
    if(fp ==NULL){
        return NULL;
    }
    
    bytes_remaining = buf.st_size;
    
    
    // doesnt return it a void pointer here? if i doesnt convert types?
    // TODO: there must be a better solution this is hard to read for me
    p = buffer =(char *) malloc(bytes_remaining);
    
    
    if(buffer == NULL){
        return NULL;
    }
    
    while(bytes_read = fread(p, 1, bytes_remaining, fp), bytes_read != 0 && bytes_remaining > 0 ){
        if(bytes_read == -1 ){
            free(buffer);
            return NULL;
        }
        
        bytes_remaining -= bytes_read;
        p += bytes_read;
        total_bytes += bytes_read;
    }
    
    struct file_data *filedata = (struct file_data*) malloc(sizeof filedata);

        if (filedata == NULL) {
            free(buffer);
            return NULL;
        }

        filedata->data = buffer;
        filedata->size = total_bytes;

        return filedata;
    
}

/*
  free the allocated memory in heap
 */
void file_free(struct file_data* filedata){
    
    free(filedata);
    free(filedata->data);

}
