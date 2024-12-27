#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* key;
    char* value;
    struct Node* next;
};
struct LinkedList {
    struct Node* head;
    size_t size;
};

struct Hashmap {
    struct LinkedList** buckets; // Each bucket will contain a linked list 
    size_t size;
};

typedef struct LinkedList LinkedList;
typedef struct Hashmap Hashmap;
typedef struct Node Node;

Hashmap* createHashmap(int bucket_count);


long hashingFunction(char* s);

int insert(Hashmap* map, char* key, char* value);

char* get(Hashmap* map, char* key);

void freeHashmap(Hashmap* map);

int deleteKey(Hashmap* map, char* key);

int exists(Hashmap* map, char* key);

Hashmap* resizeHashmap(Hashmap* map);
#endif