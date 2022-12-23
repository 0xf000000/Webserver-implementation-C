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

extern int Listlength(struct list *List);
extern struct list* createList(void);
extern void Push (struct list *headRef, int data);
extern void appendNode(struct list *HEAD, int data);
extern int getListHead(struct list *list);
extern int getListTail(struct list *list);


#endif /* list_h */
