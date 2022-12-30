//
//  list.h
//  WebserverC
//
//  Created by Leon Margale on 19.12.22.
//

#ifndef list_h
#define list_h

struct node{
    void* data;
    struct node *next;
};

struct list{
    struct node *head;
    int count;
    
};

extern int Listlength(struct list *List);
extern struct list* createList(void);
extern void Push (struct list *headRef, void* data);
extern void* appendNode(struct list *HEAD, void* data);
extern void* getListHead(struct list *list);
extern void* getListTail(struct list *list);
extern void foreachNode(struct list* list, void (*f)(void*,void*), void *args);
extern void destroyList(struct list *mylist);
extern void freeArray(int** array);
extern void *deleteNode(struct list *mylist, void *data, int (*cmpfn)(void *, void *));
extern void* listFind(struct list* mylist, void *data, int (*compare) (void*, void*));
#endif /* list_h */
