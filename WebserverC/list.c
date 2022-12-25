//
//  list.c
//  WebserverC
//
//  Created by Leon Margale on 19.12.22.
//
#include <stdio.h>
#include <stdlib.h>
#include "list.h"




/*
 creates a List
 returns a struct list pointer
 */


struct list* createList(void){
    
    struct list* list = calloc(1 , sizeof(struct list));

    
    return list;
    
}

/*
 when we have a list struct it makes the programming of the linked list a bit easier cause we dont have to deal with pointer references anymore
 */
void Push (struct list* mylist , int data) {
    struct node* newNode = malloc(sizeof(struct node));
    
    if(newNode == NULL){
        return;
    }
    
    newNode -> data = data;
    newNode -> next =  mylist -> head;
    
    mylist -> head = newNode;
    
    
}

/*
 appending a node to the end of our list
 */
void appendNode(struct list *list, int data){
    
    
    
    struct node *current = list -> head;
    struct node *newNode = malloc(sizeof(struct node));
    
    newNode -> data = data;
    newNode -> next = NULL;
    
    
    // special case if the first head pointer is NULL
    if(current == NULL ){
        Push(list, data);
        return;
    }
    
    else{
        
        
        while(current -> next != NULL){
            current = current -> next;
        }
        
        current -> next = newNode;
        
       
        
    }
    // returns the first data that got inserted
    
}

/**
returns the length of our Linked list in an Integer
 */

int Listlength(struct list *List){
    struct node* head = List -> head;
    
    // count is set to 1 because if the head Pointer is NULL there are no list ELEMENTS so it will return 0
    // so if it doesnt there is always at least one Element. And my Brain wasnt smart enough for a better solution 
    int count = 1;
    
    
    // if the list has no components
    if(List -> head == NULL){
        return 0;
    }
    
    
    while(head -> next != NULL){
        
        count++;
        
        head = head -> next;
    }
    
    return count;
    
}

// returns the data of our first element in the list
int getListHead(struct list *list){
    
    struct node* head = list -> head;
    
    // if the head is null
    if(head == NULL ){
        return -1;
    }
    
    return head -> data;
    
}


// returns the last element in our list

int getListTail(struct list *list){
    
    struct node* current = list -> head;
    
    
    if(current == NULL ){
        return -1;
    }else{
        
        
        while(current -> next != NULL){
            
            current = current -> next;
        }
        
        return current -> data;
    }
}



int** listToArray(struct list* mylist ){
   
    if(mylist -> head == NULL){
        return 0;
    }
    
    // allocate a array for the size of your list
    int** a = malloc(Listlength(mylist) * sizeof(int));
    
    
    struct node* current  = mylist -> head;
    int i;
    for(i = 0; current != NULL; i ++,current = current-> next ){
        
        
        *a[i] = current -> data;
        
    }
    
    
    *a[i] = 0;
    
    
    
    return a;
}


void freeArray(int** array){
    
    free(array);
    
}



void destroyList(struct list *mylist){
    
    struct node *current = mylist -> head, *next;
    
    while(current != NULL){
        
        next = current -> next;
        
        free(current);
        
    }
    
    free(mylist);
    
}

/*
 runns a function for each node
 TODO: needs to be changed so it takes a void pointer
 */

void foreachNode(struct list* list, void (*f)(int,void*), void *args){
    
    struct node* current = list -> head;
    
    while(current != NULL){
        
        f( current -> data, args);
        
        current = current -> next;
    }
    
}

/**
 finds a data element and returns it inside of our list
 if it is not in our list this function will return NULL
 */

int* listFind(struct list* mylist, int *data, int (*compare) (void*, void*) ){
    struct node* current = mylist-> head;
    
    if(current == NULL){
        return NULL;
    }
    
    while(current != NULL){
        
        if(compare(data, &current -> data) == 0){
            
            
            break;
        }
        
        
        current = current-> next;
    }
    
    if(current == NULL){
        
        
        
        return NULL;
    }
    
    
    
    
    return &current -> data;
    
    
    
}

// deletes a Node inside of our list
void *deleteNode(struct list *mylist, void *data, int (*compare)(void *, void *)){
    
    struct node* current = mylist -> head, *prev = NULL;
    
    while(current != NULL){
       
        
        if(compare(data, &current-> data) == 0 ){
            
            // this is if case head should get deleted
            if(prev==NULL){
                mylist-> head = current-> next;
                
                free(current);
            }else{
                
                prev -> next = current -> next;
                
                free(current);
                
            }
            
            return data;
            
          
        }
        
        
        prev = current;
        current = current -> next;
    }
 
    
    return NULL;
    
    
    
}
    
    
    
    








