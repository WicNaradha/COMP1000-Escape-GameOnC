/* 
    Written by : W.M.Naradha
    Student ID : 20469160
    Date - Version_0: 03/Oct/2022 (Not Generic Linked List)
    Date - Version_0.1: 05/Oct/2022 (Generic Linked List)
    Date - Version_0.2: 09/Oct/2022

    Handle Lists in the game
*/

#include "list.h"

/**
    *@brief Function called to make a given node
    *@note  The function makes the node given as input
    *@param node : pointer to listnode
    *@param data : void pointer to data
    *@param next : pointer to next listnode
    *@param node : pointer to previous listnode
    *@retval void
*/

static void makenode(ListNode* node, void* data, ListNode* next, ListNode* prev)
{
    node->data = data;
    node->next = next;
    node->prev = prev;
}

/**
    *@brief Function called to return a created node
    *@note  The function creates and returns a pointer to a node
    *@param data : void pointer to data
    *@param next : pointer to next listnode
    *@param node : pointer to previous listnode
    *@retval ListNode*
*/

static ListNode* returnnode(void* data, ListNode* next, ListNode* prev)
{
    ListNode* node = (ListNode*)calloc(1,sizeof(ListNode));
    node->data = data;
    node->next = next;
    node->prev = prev;
    return node;
}

/**
    *@brief Function called to free a created node
    *@note  The function frees a node
    *@param node : pointer to listnode to be freed
    *@param data : void pointer to data
    *@param next : pointer to next listnode
    *@param node : pointer to previous listnode
    *@retval void
*/

static void freenode(ListNode* node, ListHead *list, void (*freedata)(void*))
{
    (*freedata)(node->data);
    free(node);
    list->size--;
}

/**
    *@brief Function called to return a created list
    *@note  The function creates and returns a pointer to a list
    *@retval ListHead* (Pointer to an empty listhead)
*/

ListHead* makelist()
{
    ListHead* list = (ListHead*)calloc(1,sizeof(ListHead));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

/**
    *@brief Function called to make a given node
    *@note  The function makes the node given as input
    *@param list : pointer to list to add data to
    *@param data : void pointer to data to be appended
    *@retval void
*/

void appendlist(ListHead *list, void *data)
{
    ListNode *appnode = (ListNode*)calloc(1,sizeof(ListNode));
    ListNode *endnode;

    if (list->size == 0)
    {
        makenode(appnode,data,NULL,NULL);
        list->head = appnode;
        list->tail = appnode;
    }
    else
    {
        endnode = list->tail;
        makenode(appnode,data,NULL,endnode);
        endnode->next = appnode; 
        list->tail = appnode;       
    }

    list->size++;
}

/**
    *@brief Function called to add data at a point into the list
    *@note  The function adds the data to a point
    *@param list : pointer to list to add data to
    *@param data : void pointer to data to be appended
    *@param pnt : position to add data to    
    *@retval void
*/

/* TODO : Test this function if you can before submission. */
/* PERF : This is not used and append is more effective */

void addatlist(ListHead *list, void *data, int pnt)
{
    int i;

    ListNode *addatnode = (ListNode*)calloc(1,sizeof(ListNode));
    ListNode *fnode, *lnode;
    
    fnode = list->head;
    lnode = list->tail;

    if (pnt == 0)
    {
        makenode(addatnode,data,fnode->next,lnode->prev);
        list->head = addatnode;
        list->tail = addatnode;
        list->size++;
    }
    else if (pnt < list->size)
    {
        for (i = 0; i < pnt ; i++)
        {
            fnode = fnode->next;
            lnode = fnode->next;
        }
        makenode(addatnode,data,fnode->next,lnode->prev);
        fnode->next = addatnode;
        lnode->prev = addatnode;
        list->size++;         
    }
    else 
    {
        printf("Pnt out of list bounds - addat!\n");
    }
}

/**
    *@brief Function called to clear the data and nodes of a list
    *@note  The function makes removes all nodes and data of a list
    *@param list : pointer to list to be cleared
    *@retval void
*/

void clearlist(ListHead *list)
{
    ListNode *fnode ,*node = list->tail;
    void (*freefunc)(void*);
    freefunc = &free;
    while(list->size > 1)
    {
        fnode = node;
        node = node->prev;
        freenode(fnode,list,freefunc);
    }
    freenode(node,list,freefunc);
}

/**
    *@brief Function called to move data from one list to another (NOT COPY!)
    *@note  The function moves all data in one list and sets it as the data in another (Clearing the original list)
    *@param list : pointer of source list
    *@retval list with moved data
*/

ListHead* movelistdata(ListHead *source)
{
    ListNode *snode, *dnode, *node;
    ListHead *destination = makelist();

    while(destination->size < source->size)
    {
        if (destination->size == 0)
        {
            snode = source->head;
            dnode = returnnode(snode->data,NULL,NULL);
            destination->head = dnode;
            destination->tail = dnode;
            destination->size++; 
        }
        else
        {
            node = returnnode(snode->data,NULL,dnode);
            dnode->next = node;
            dnode = dnode->next; 
            destination->tail = dnode;
            destination->size++;  
        }
        snode->data = NULL;
        snode = snode->next;
    }

    return destination;
}

/**
    *@brief Function called to free the entire list
    *@note  The function frees the entire list
    *@param list : pointer of list to be freed
    *@param freedata : function pointer to function to free data.
    *@retval void
*/

void freelist(ListHead *list, void (*freedata)(void*))
{
    int i;
    ListNode *ptr = list->tail;
    for (i = (list->size); i > 0; i--)
    {
        if (i == 1)
        {
           freenode(ptr,list,freedata);
        }
        else
        {
            ptr = ptr->prev;
            freenode(ptr->next,list,freedata);
        }
    }  
    free(list);
}

/**
    *@brief Function called to free the last entity of the list
    *@note  The function frees the last node of the list
    *@param list : pointer of list to have last entity freed
    *@param freedata : function pointer to function to free data.
    *@retval void
*/

void freenodelast(ListHead* list,void (*freedata)(void*))
{
    ListNode *fnode, *node;
    node = list->tail;

    if (node->prev != NULL)
    {
        fnode = node->prev;
        list->tail = fnode;
    }
    else
    {
        list->tail = NULL;
        list->head = NULL;
    }

    freenode(node, list, freedata);
}

/**
    *@brief Function called to free the last entity of the list
    *@note  The function frees the last node of the list
    *@param list : pointer of list to have last entity freed
    *@param freedata : function pointer to function to free data.
    *@param pnt : position to add data to 
    *@retval void
*/

void freenodeat(ListHead* list,void (*freedata)(void*),int pnt)
{
    int i;
    ListNode *fnode, *bnode, *node;
    if ((pnt <= list->size) && (pnt > 0))
    {
        for (i=0; i<pnt; i++)
        {
            if (i == 0)
            {
                node = list->head;
            }
            else
            {
                node = node->next;
            }
        }

        bnode = node->prev;
        fnode = node->next;

        if (bnode != NULL)
        {
            bnode->next = fnode;
        }
        else
        {
            fnode->prev = NULL;
            list->head = fnode;
        }

        if (fnode != NULL)
        {
            fnode->prev = bnode;
        }
        else
        {
            bnode->next = NULL;
            list->tail = bnode;
        }

        freenode(node, list, freedata);
    }
    else
    {
        printf("Pnt out of list bounds - freeat!\n");
    }
}

/**
    *@brief Function called to read the first element of the list
    *@note  The function returns a void* to the data in the first element
    *@param list : pointer of list
    *@retval void*
*/

void* readfirst(ListHead *list)
{
    ListNode *readnode;
    readnode = list->head;
    return readnode->data;
}

/**
    *@brief Function called to read the last element of the list
    *@note  The function returns a void* to the data in the last element
    *@param list : pointer of list
    *@retval void*
*/

void* readlast(ListHead *list)
{
    ListNode *readnode;
    readnode = list->tail;
    return readnode->data;
}

/**
    *@brief Function called to read the last element of the list
    *@note  The function returns a void* to the data in the last element
    *@param list : pointer of list
    *@param int : data in list to read at
    *@retval void*
*/

void* readatlist(ListHead *list, int pnt)
{
    int i;
    void* out = NULL;

    ListNode *readnode;
    readnode = list->head; 
    if (pnt <= list->size)
    {
        for (i = 0; i < pnt ; i++)
        {
            if (i == 0)
            {
                readnode = list->head;
            }
            else
            { 
                readnode = readnode->next;
            }
        }
        out = readnode->data;
    }
    else 
    {
        printf("Pnt out of list bounds - readat!\n");
    }    
    
    return out;
}