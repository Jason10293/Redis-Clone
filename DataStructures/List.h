#ifndef LIST_H
#define LIST_H
#include "DoublyLinkedList.h"

struct List {
    DoublyLinkedList* list;
};

typedef struct List List;

List* createList();
void LPUSH(List* list, char* elem);
void RPUSH(List* list, char* elem);
// char** LPOP_COUNT(List* list, int count);
// char** RPOP_COUNT(List* list, int count);
char* LPOP(List* list);
char* RPOP(List* list);
void freeList(List* list);
void printList(List* list);


#endif