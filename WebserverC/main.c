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
#include "cache.h"
// implement a parameter handler here or a config file to change this
#define PORT "8080"
#define SERVER "John/0.01"
#define SERVER_FILES "/Users/leon/Code/WebserverC/WebserverC/serverfiles/"
#define SERVER_ROOT "/Users/leon/Code/WebserverC/WebserverC/serverroot"
#define STATUSCODE200 "HTTP/1.1 200 OK"
#define STATUSCODE404 "HTTP/1.1 404 NOT FOUND"
#define RANDOMINTEGERVALUE 20
#define PLANEMIMETYPE "text/plain"
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
            "Content-Length: %d\n\n"
            "%s\n "
            ,header,contend_type,date,SERVER, contentLength, body);
    
    printf("here is the current response %s ",response);
    
    int rv = send(fd, response, strlen(response),0);
    
    if (rv < 0 ){
        perror("send() function ");
    }
    return rv;
}

int generateRandomNumber(void){
    srand(time(NULL));
    return rand() % RANDOMINTEGERVALUE -1;
}

void get_d20(int socket){

    // generate a random number between 1 and 20
    char numberRange[][2] = {'0','1','2','3','4','5','6','7','8','9',"10","11","12","13","14","15","16","17","18","19","20"};
    int randomInteger = generateRandomNumber();
   
    // for one digit one char integer
    if(randomInteger < 10 ){
        char SingleInteger;
        SingleInteger = numberRange[randomInteger][0];
        sendResponse(socket, STATUSCODE200, PLANEMIMETYPE,&SingleInteger , 1);
        return;
    }
    
    // Send to digit response back
    char integerToSendBack[2];
    for(int i =0; i < sizeof numberRange[randomInteger]; i++ ){
        integerToSendBack[i] = numberRange[randomInteger][i];
    }
    
    sendResponse(socket, STATUSCODE200, PLANEMIMETYPE,&integerToSendBack , 2);
    // sends the number back to the requester as text/plain
    
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
    
    
    sendResponse(fd, STATUSCODE404, mime_type, filedata->data, filedata->size);
    
    file_free(filedata);
}



void handleHttpRequest(int fd, struct cache* cache ){
    
    const int requestBufferSize = 6536;
    char request[requestBufferSize];
    char method[20];
    char path[200];
    // read request
    
    int bytes_recvd = recv(fd, request, requestBufferSize -1, 0);
    
    if(bytes_recvd  < 0){
        perror("recv handleHttpRequest function something wrong with the request");
        return;
    }
    
    // get the method and the path
    sscanf(request, "%s %s", method, path);
    
    // handle GET endpoint
    if(strcmp(method, "GET") == 0 ){
        
        
        if(strcmp(path, "/d20") == 0 ){
           
            get_d20(fd);
            return;
        }
        
        
       struct cacheEntry* entry =  cacheGet(cache, path);
        
        if(entry != NULL){
            
            sendResponse(fd, STATUSCODE200, entry->content_type, entry->content, entry->content_length);
            return;
        }
        
        
        
        char filepath[4000];
        
        sprintf(filepath, "%s%s", SERVER_ROOT, path);
        
        
        
        
        // file is not in cache and get loaded from Disk
        
        struct file_data*  file = loadFile(filepath);
        
        if(file == NULL ){
            resp_404(fd);
            return;
        }
       
        
        
        char *mimetype = getMIMEtype(filepath);
        cachePut(cache, path, mimetype, file->data, file->size);
        
        sendResponse(fd, STATUSCODE200 , mimetype, file->data, file->size);
        
        file_free(file);
    }
    
    if(strcmp(method, "POST" ) == 0 ){
        //TODO: keine ahnung wie man ne POST request handelt database Connectivity?
    }
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
    struct cache* cache = cacheCreate(6, 6);
    
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
        
        handleHttpRequest(newfd, cache);
        
        printf("response Sended");
        
        // newfd gets passed on every time to handle our connection with the client and gets closed after the parsing of our request
        close(newfd);
        
    }
    
    
    //should be unreachable
    
    return 0;
}
