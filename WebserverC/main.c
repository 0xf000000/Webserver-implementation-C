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
#include "table.c"

// implement a parameter handler here or a config file to change this
#define PORT "8080"
#define SERVER "Server: John/0.01"

 /*
  * Send an HTTP response
  *
  * header:       "HTTP/1.1 404 NOT FOUND" or "HTTP/1.1 200 OK", etc.
  * content_type: "text/plain", etc.
  * body:         the data to send.
  *
  * Return the value from the send() function.
  
  
  "HTTP/1.1 200 OK\n"
  "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
  "Server: Apache/2.2.3\n"
  "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
  "ETag: \"56d-9989200-1132c580\"\n"
  "Content-Type: text/html\n"
  "Content-Length: 15\n"
  "Accept-Ranges: bytes\n"
  "Connection: close\n"
  "\n"
  "sdfkjsdnbfkjbsf";
  */
 
int sendResponse(int fd, char *header, char *contend_type, void *body, int contentLength){
    const int maxResponseSize = 262144;
    char response[maxResponseSize];
    
    
    //sprintf(response, "%s\n",header);
    time_t rawtime;
    struct tm* info;
    time(&rawtime);
    info = localtime(&rawtime);
    char *date = asctime(&rawtime);
    
    sprintf(response, "%s\n Date: %s\n %s\n  Conntent-Type: %s\n ",header,date, SERVER,contend_type);
    
    return 0;
}

void handleHttpRequest(int fd){
    
    
    
    
    
    
}


int main(int argc, const char * argv[]) {
    
    
    
    
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
