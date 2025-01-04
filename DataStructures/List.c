#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "DoublyLinkedList.h"
List* createList() {
    List* list = malloc(sizeof(List));
    DoublyLinkedList* DLL = malloc(sizeof(DoublyLinkedList));
    DLL->head = NULL;
    DLL->tail = NULL;
    DLL->size = 0;
    list->list = DLL;
    return list;
}
void LPUSH(List* list, char* elem) {
    DoublyLinkedList* DLL = list->list;
    DLL_Node* node = malloc(sizeof(DLL_Node));
    node->elem = strdup(elem);
    node->next = DLL->head;
    node->prev = NULL;
    if (DLL->size != 0) {
        DLL->head->prev = node;
    } else {
        DLL->tail = node;
    }
    DLL->head = node;
    DLL->size += 1;
}
void RPUSH(List* list, char* elem) {
    DoublyLinkedList* DLL = list->list;
    DLL_Node* node = malloc(sizeof(DLL_Node));
    node->elem = strdup(elem);
    node->next = NULL;
    node->prev = DLL->tail;
    if (DLL->size != 0) {
        DLL->tail->next = node;
    } else {
        DLL->head = node;
    }
    DLL->tail = node;
    DLL->size += 1;
}

char* LPOP(List* list) {
    DoublyLinkedList* DLL = list->list;
    if (DLL->size == 0) {
        return "No elements in list";
    }
    DLL_Node* node = DLL->head;
    char* node_val = strdup(node->elem);
    DLL->head = DLL->head->next;
    if (DLL->head != NULL) {
        DLL->head->prev = NULL;
    } else {
        DLL->tail = NULL;
    }
    free(node->elem);
    free(node);
    DLL->size -= 1;
    return node_val;
}
char* RPOP(List* list) {
    DoublyLinkedList* DLL = list->list;
    if (DLL->size == 0) {
        return "No elements in the list";
    }
    DLL_Node* node = DLL->tail;
    char* node_val = strdup(node->elem);
    DLL->tail = DLL->tail->prev;
    if (!DLL->tail) {
        DLL->head = NULL;
    } else {
        DLL->tail->next = NULL;
    }
    DLL->size -= 1;
    free(node->elem);
    free(node);
    return node_val;
}
void freeList(List* list) {
    DoublyLinkedList* DLL = list->list;
    DLL_Node* node = DLL->head;
    while (node) {
        DLL_Node* tmp = node;
        node = node->next;
        free(tmp->elem);
        free(tmp);
    }
    free(DLL);
    free(list);
}
void printList(List* list) {
    DoublyLinkedList* DLL = list->list;
    DLL_Node* current = DLL->head;
    while (current != NULL) {
        printf("%s ", current->elem);
        current = current->next;
    }
    printf("\n");
}