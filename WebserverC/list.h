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

struct list{
    struct node *head;
    int count;
    
};

struct list* createList(void);
void Push (struct node **headRef, int data);
extern void appendNode(struct node **HEAD, int data);
extern void *list_head(struct node *list);



#endif /* list_h */
