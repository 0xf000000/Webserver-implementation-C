#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/file.h>
#include <fcntl.h>
#include "net.h"
#include "file.h"
#include "list.h"

// implement a parameter handler here or a config file to change this
#define PORT "8080"


int main(int argc, const char * argv[]) {
   struct list *mylist =  createList();
   
  
    
    int lengthOfList = getListTail(mylist) ;
    
    printf(" this is the listlenght %i ",lengthOfList);
    
    struct sockaddr_storage their_addr;
    int newfd;
    char InetAdress[INET6_ADDRSTRLEN];
    
    // get a listening socket that is bounded to a Interface
    //listenfd will listen every time for a new connection
    int listenfd = get_socket(PORT);
    
    if(listenfd < 0){
        fprintf(stderr, "Webserver: fatal error getting the listening socket\n");
        exit(1);
    }
    
    printf("webserver: waiting for connection on port %s ..\n", PORT);
    
    while(1){
        socklen_t sin_size = sizeof their_addr;
        
        // waits for a new connection ...
        newfd = accept(listenfd,(struct sockaddr *) &their_addr, &sin_size);
        
        if(newfd == -1 ){
            perror("accept");
            continue;
        }
        
        // gets us a Inet address
        inet_ntop(their_addr.ss_family, getInetAdress((struct sockaddr * ) &their_addr), InetAdress, sizeof InetAdress );
        
        printf("server: got connection from %s\n",InetAdress);
        
        
        
        //handle_http_request()
        
        // newfd gets passed on every time to handle our connection with the client and gets closed after the parsing of our request
        close(newfd);
        
    }
    
    
    //should be unreachable
    
    return 0;
}
