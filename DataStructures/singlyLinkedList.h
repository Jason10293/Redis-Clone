#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

struct SLL_Node {
    char* key;
    char* value;
    struct SLL_Node* next;
};
struct LinkedList {
    struct SLL_Node* head;
    size_t size;
};

typedef struct LinkedList LinkedList;
typedef struct SLL_Node SLL_Node;
#endif