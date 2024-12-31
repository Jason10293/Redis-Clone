#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singlyLinkedList.h"

struct Hashmap {
    struct LinkedList** buckets; // Each bucket will contain a linked list 
    size_t size;
    int bucket_count;
};

typedef struct Hashmap Hashmap;

Hashmap* createHashmap(int bucket_count);

long hashingFunction(char* s);

int insert(Hashmap* map, char* key, char* value);

char* get(Hashmap* map, char* key);

void freeHashmap(Hashmap* map);

int deleteKey(Hashmap* map, char* key);

int exists(Hashmap* map, char* key);

Hashmap* resizeHashmap(Hashmap* map);
#endif