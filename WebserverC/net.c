//
//  net.c
//  WebserverC
//
//
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "net.h"

#define BACKLOG 10


/*
 basically a function that helps getting the current InetAdress which we use
 
 */

void *getInetAdress(struct sockaddr *sa){
    
    //
    if(sa -> sa_family == AF_INET) return &(((struct sockaddr_in*)sa)-> sin_addr);
    
    //returns a struct pointer to the sin6_addr
    // the pointer gets also casted into 'struct sockaddr_in6*'
    return &(( (struct sockaddr_in6*) sa) -> sin6_addr);
}

/*
 this function implements the functionality of creating a socket and binding it to a Networkinterface
 it returns a Listening Socket and takes a char pointer
 */

int get_socket(char *port){
    int sockfd = 0;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int yes = 1;
    
    // here memset gets used to fill the memory used for memset with 0, and relocate new things there
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    // if rv is != 0 there is a problrem with our interfaces this is error handling here
    
    if((rv = getaddrinfo(NULL, port , &hints, &servinfo)) != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
    }
    
    // looping trough all the network interfaces that are currently on our machine
    // TODO: make this function a bit more less complex and human redable
    for(p = servinfo; p != NULL; p = p -> ai_next){
        
        if((sockfd = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) == -1 ){
            continue;
        }
        
        //SO_REUSEADDR prevents the 'address aleready in use' errors
        if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 ){
            perror("setsocketopt");
            close(sockfd);
            freeaddrinfo(servinfo);
            return -2;
        }
        
        
        // we try to bind our Socket to our ip adress
        if(bind(sockfd, p ->ai_addr, p->ai_addrlen) == -1){
            close(sockfd);
            continue;
        }
        
        
        break;
    }
    
    // free memory from the structs in heap
    freeaddrinfo(servinfo);
    
    // if p is null then we dont have a good socked
    if(p == NULL){
        fprintf(stderr, "webserver: failed to find local address\n");
        return -3;
    }
    
    if(listen(sockfd,BACKLOG) == -1 ){
        
        close(sockfd);
        return -4;
    }
    
    
    return sockfd;
}
