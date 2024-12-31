#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "doublyLinkedList.h"

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
    node->elem = elem;
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

void printList(List* list) {
    DoublyLinkedList* DLL = list->list;
    DLL_Node* current = DLL->head;
    while (current != NULL) {
        printf("%s ", current->elem);
        current = current->next;
    }
    printf("\n");
}