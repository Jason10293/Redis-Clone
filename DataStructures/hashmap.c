#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singlyLinkedList.h" // Ensure correct path
#include "hashmap.h"
#define DEFAULT_BUCKET_COUNT 256
#define PRIME_NUM 3411949
#define CAPACITY_THRESHHOLD 0.75

Hashmap* createHashmap(int bucket_count) {
    LinkedList** bucketsArr = malloc(bucket_count * sizeof(LinkedList*));
    for (int i = 0; i < bucket_count; i++) {
        bucketsArr[i] = malloc(sizeof(LinkedList));
        bucketsArr[i]->head = NULL;
        bucketsArr[i]->size = 0;
    }
    Hashmap* map = malloc(sizeof(Hashmap));
    map->buckets = bucketsArr;
    map->size = 0;
    map->bucket_count = bucket_count;
    return map;
}

long hashingFunction(char* s) {
    long hash = 0;
    while (*s != '\0') {
        hash = PRIME_NUM * hash + *s++;
    }
    return hash < 0 ? -hash : hash; // Ensure positive hash value
}

Hashmap* resizeHashmap(Hashmap* map) {
    int new_bucket_count = map->bucket_count * 2;
    LinkedList** new_buckets = malloc(new_bucket_count * sizeof(LinkedList*));

    for (int i = 0; i < new_bucket_count; i++) {
        new_buckets[i] = malloc(sizeof(LinkedList));
        new_buckets[i]->head = NULL;
        new_buckets[i]->size = 0;
    }

    for (int i = 0; i < map->bucket_count; i++) {
        LinkedList* bucket = map->buckets[i];
        SLL_Node* current = bucket->head;
        while (current) {
            int new_index = hashingFunction(current->key) % new_bucket_count;
            SLL_Node* new_node = malloc(sizeof(SLL_Node));
            new_node->key = strdup(current->key);
            new_node->value = strdup(current->value);
            new_node->next = new_buckets[new_index]->head;
            new_buckets[new_index]->head = new_node;
            new_buckets[new_index]->size++;

            SLL_Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
        free(bucket);
    }

    free(map->buckets);
    map->buckets = new_buckets;
    map->bucket_count = new_bucket_count;
    return map;
}

int insert(Hashmap* map, char* key, char* value) {
    if ((double)map->size / map->bucket_count >= CAPACITY_THRESHHOLD) {
        map = resizeHashmap(map);
    }

    int bucketIndex = hashingFunction(key) % map->bucket_count;
    LinkedList* bucket = map->buckets[bucketIndex];
    SLL_Node* n = bucket->head;
    while (n) { // Update value if the key already exists
        if (strcmp(n->key, key) == 0) {
            free(n->value);
            n->value = strdup(value);
            return 1;
        }
        n = n->next;
    }
    n = malloc(sizeof(SLL_Node));
    if (!n) return -1; // Check if memory allocation failed
    n->key = strdup(key);
    if (!n->key) {
        free(n);
        return -1;
    }
    n->value = strdup(value);
    if (!n->value) {
        free(n->key);
        free(n);
        return -1;
    }
    n->next = bucket->head;
    bucket->head = n;
    bucket->size += 1;
    map->size += 1; // Increment map size after successful insertion
    return 1;
}


char* get(Hashmap* map, char* key) {
    int bucketIndex = hashingFunction(key) % map->bucket_count;
    LinkedList* bucket = map->buckets[bucketIndex];
    SLL_Node* n = bucket->head;
    while (n) {
        if (strcmp(key, n->key) == 0) {
            return n->value;
        }
        n = n->next;
    }
    return NULL;
}

void freeHashmap(Hashmap* map) {
    for (int i = 0; i < map->bucket_count; i++) { // Fix loop condition
        LinkedList* bucket = map->buckets[i];
        SLL_Node* tmp = bucket->head;
        while (bucket->head) {
            tmp = bucket->head;
            bucket->head = bucket->head->next;
            free(tmp->key); // Free the key
            free(tmp->value); // Free the value
            free(tmp);
        }
        free(bucket);
    }
    free(map->buckets);
    free(map);
}

int deleteKey(Hashmap* map, char* key) {
    int bucketIndex = hashingFunction(key) % map->bucket_count;
    LinkedList* bucket = map->buckets[bucketIndex];
    SLL_Node* n = bucket->head;
    SLL_Node* prev = NULL;

    while (n) {
        if (strcmp(n->key, key) == 0) {
            if (prev) {
                prev->next = n->next;
            } else {
                bucket->head = n->next;
            }
            free(n->key);
            free(n->value);
            free(n);
            bucket->size -= 1;
            return 1;
        }
        prev = n;
        n = n->next;
    }
    return -1;
}

int exists(Hashmap* map, char* key) {
    int bucketIndex = hashingFunction(key) % map->bucket_count;
    LinkedList* bucket = map->buckets[bucketIndex];
    SLL_Node* n = bucket->head;
    while (n) {
        if (strcmp(n->key, key) == 0) {
            return 1;
        }
        n = n->next; // Ensure iteration through the list
    }
    return 0;
}
