//
//  list.h
//  WebserverC
//
//  Created by Leon Margale on 19.12.22.
//

#ifndef list_h
#define list_h

struct node{
    int data;
    struct node *next;
};

struct node* createList(int data);
void Push (struct node **headRef, int data);



#endif /* list_h */
