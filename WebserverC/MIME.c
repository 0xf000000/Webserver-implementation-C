//
//  MIME.c
//  WebserverC
//
//
//
#include <string.h>
#include <ctype.h>
#include "MIME.h"
#define DEFAULT_MIME_ "application/octet-stream"



char *strlower(char *s){
    
    for(char *p = s; *p =! '\0';p++){
        *p = tolower(*p);
    }
    return s;
}

/**
 should return a memetype for the requested file
 */

char *mime_type_get(char *filename){
    char *ext = strrchr(filename,'.');
    
    if(ext == NULL){
        return DEFAULT_MIME_;
    }
    
    ext++;
    
    strlower(ext);
        
    //TODO: we can acctually implement this with a map will do this later we need O(1)
    
    if(strcmp(ext, "html")  == 0 ||
       strcmp(ext, "htm")   == 0  ) return "text/html";
    if(strcmp(ext, "css")   == 0  ) return "text/css";
    if(strcmp(ext, "js")    == 0  ) return "application/javascript";
    if(strcmp(ext, "html")  == 0  ) return "text/html";
    if(strcmp(ext, "json")  == 0  ) return "application/json";
    if(strcmp(ext, "txt")   == 0  ) return "text/plain";
    if(strcmp(ext, "png")   == 0  ) return "image/png";
    if(strcmp(ext, "gif")  == 0   ) return "image/gif";
    if(strcmp(ext, "php") == 0    ) return "";
    
    
    return DEFAULT_MIME_;
}


