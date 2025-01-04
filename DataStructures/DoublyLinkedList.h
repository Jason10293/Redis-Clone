#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stdlib.h>

struct DLL_Node {
    char* elem;
    struct DLL_Node* next;
    struct DLL_Node* prev;
};

struct DoublyLinkedList {
    size_t size;
    struct DLL_Node* head;
    struct DLL_Node* tail;
};

typedef struct DoublyLinkedList DoublyLinkedList;
typedef struct DLL_Node DLL_Node;

#endif 