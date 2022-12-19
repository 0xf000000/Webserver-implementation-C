//
//  list.c
//  WebserverC
//
//  Created by Leon Margale on 19.12.22.
//
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 just a function to test things
 */
struct node* buildOnetwoThree(){
    
    struct node* head = malloc(sizeof(struct node));
    struct node* second = malloc(sizeof(struct node));
    struct node* third = malloc(sizeof(struct node));
    
    head -> next = second;
    head -> data = 1;
    
    second -> next = third;
    third -> next = NULL;
    
    
    
    
    
    return head;
}


struct node* createList(int data){
    struct node* HEAD = malloc(sizeof(struct node));
    
    HEAD -> data = data;
    HEAD -> next = NULL;
    
    return HEAD;
    
}

/*
 basically we have a pointer which is pointing to our head node,
 we insert our newNode and make it the
 */
void Push (struct node **headRef, int data) {
    struct node* newNode = malloc(sizeof(struct node));
    
    newNode -> data = data;
    newNode -> next = *headRef;
    
    *headRef = newNode;
    
}


