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
#include "table.h"
#include "MIME.h"
// implement a parameter handler here or a config file to change this
#define PORT "8080"
#define SERVER "Server: John/0.01"
#define SERVER_FILES "/Users/leon/Code/WebserverC/WebserverC/serverfiles/"
#define SERVER_ROOT "./serverRoot"

 /*
  * Send an HTTP response
  *
  * header:       "HTTP/1.1 404 NOT FOUND" or "HTTP/1.1 200 OK", etc.
  * content_type: "text/plain", etc.
  
  
  * body:         the data to send.
  *
  * Return the value from the send() function.
  really important to leave 1 or 2 spaces in the http function 
  
  
  */
 
int sendResponse(int fd, char *header, char *contend_type, void *body, int contentLength){
    const int maxResponseSize = 262144;
    char response[maxResponseSize];
    
    
    //sprintf(response, "%s\n",header);
    char date[1000];
    time_t now = time(0);
    struct tm tm = *gmtime(&now);
    strftime(date, sizeof date , "%a, %d %b %Y %H:%M:%S %Z", &tm);
   
    sprintf(response,
            "%s\n"
            "Content-Type: %s\n"
            "Date: %s\n"
            "Server: %s\n"
            "Content-Length: %d\n\n\n"
            " %s\n"
            ,header,contend_type,SERVER,date , contentLength, body);
    
   
    
    
    int rv = send(fd, response, strlen(response),0);
    
    if (rv < 0 ){
        perror("send() function ");
    }
    return rv;
}

void handleHttpRequest(int fd){
    
    
    
    
    
    
}

/*
 sends a 404 response to the client
 */

void resp_404(int fd){
    
    
    char filepath[4096];
    struct file_data *filedata;
    char *mime_type;
    
    // get the 404 path
    
    sprintf(filepath, "%s/404.html", SERVER_FILES);
    filedata = loadFile(filepath);
    
    
    if(filedata == NULL){
        fprintf(stderr, "cannot find system 404 file\n");
        exit(3);
    }
    
    mime_type = getMIMEtype(filepath);
    
    
    sendResponse(fd, "HTTP/1.1 404 NOT FOUND ", mime_type, filedata->data, filedata->size);
    
    file_free(filedata);
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
        
       
        
        printf("response Sended");
        //handle_http_request()
        
        // newfd gets passed on every time to handle our connection with the client and gets closed after the parsing of our request
        close(newfd);
        
    }
    
    
    //should be unreachable
    
    return 0;
}
