//
//  list.c
//  WebserverC
//
//  Created by Leon Margale on 19.12.22.
//
#include <stdio.h>
#include <stdlib.h>
#include "list.h"




struct list* createList(void){
    
    struct list* list = calloc(1 , sizeof(struct list));
    
    
    return list;
    
}

/*
 basically we have a pointer that refers to a pointer which is pointing to our head node,
 we insert our newNode and make it the
 Items will apear in reverse order as they been put in
 */
void Push (struct node **headRef, int data) {
    struct node* newNode = malloc(sizeof(struct node));
    
    newNode -> data = data;
    newNode -> next = *headRef;
    
    *headRef = newNode;
    
}

/*
 appending a node to the end of our list
 */
void appendNode(struct node **HEAD, int data){
    
    struct node *current = *HEAD;
    struct node *newNode = malloc(sizeof(struct node));
    
    newNode -> data = data;
    newNode -> next = NULL;
    
    // if there is only a head node we need to reference a pointer
    if(current -> next == NULL){
        
        current -> next = *HEAD;
        
    }else{
        
        // remember the
        while(current -> next != NULL){
            current = current -> next;
        }
        
        current -> next = newNode;
        
       
        
    }
    
    // returns the first data that got inserted
    
}

void *list_head(struct node *list){
    
    if(list -> data == 0 || list -> next == NULL){
        return NULL;
    }
    
    
    
    
    
    
    return list -> data;
    
}


