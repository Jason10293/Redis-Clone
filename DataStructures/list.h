#ifndef LIST_H
#define LIST_H
#include "doublyLinkedList.h"

struct List {
    DoublyLinkedList* list;
};

typedef struct List List;

List* createList();
void LPUSH(List* list, char* elem);
void RPUSH(List* list, char* elem);
void LPOP_COUNT(List* list, char* elem, int count);
void RPOP_COUNT(List* list, char* elem, int count);
void LPOP(List* list, char* elem);
void RPOP(List* list, char* elem);
void printList(List* list);
#endif