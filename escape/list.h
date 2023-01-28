#ifndef LIST_H
#define LIST_H

#include "macros.h"

/* Struct Declerations for Linked List */
typedef struct ListNode{
    void* data;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

typedef struct ListHead{
    int size;
    ListNode* head;
    ListNode* tail;
} ListHead;

/* Forward Declerations */
ListHead* makelist();
void appendlist(ListHead *list, void *data);
void addatlist(ListHead *list, void *data, int pnt);
void clearlist(ListHead *list);
ListHead* movelistdata(ListHead *source);
void freelist(ListHead *list, void (*freedata)(void*));
void freenodelast(ListHead *list,void (*freedata)(void*));
void freenodeat(ListHead *list,void (*freedata)(void*),int pnt);
void* readfirst(ListHead *list);
void* readlast(ListHead *list);
void* readatlist(ListHead *list,int pnt);

#endif