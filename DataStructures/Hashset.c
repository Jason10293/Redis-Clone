#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include "Hashset.h"
#define DEFAULT_BUCKET_COUNT 256

Hashset* createHashset() {
    Hashset* set = malloc(sizeof(Hashset));
    set->map = createHashmap(DEFAULT_BUCKET_COUNT);
}

void freeHashset(Hashset* set) {
    freeHashmap(set);
}

void SADD(Hashset* set, char* elem) {
    int bucketIndex = hashingFunction(elem) % set->map->bucket_count;
    LinkedList* bucket = set->map->buckets[bucketIndex];
    if (bucket->size != 0) {
        return NULL;
    }
    SLL_Node* node = malloc(sizeof(SLL_Node));
    node->key = strdup(elem);
    node->value = NULL;
    node->next = NULL;
    bucket->head = node;
    bucket->size++;
    set->map->size++;
}

void SREM(Hashset* set, char* elem) {
    int bucketIndex = hashingFunction(elem) % set->map->bucket_count;
    LinkedList* bucket = set->map->buckets[bucketIndex];
    if (bucket->size != 1) {
        return NULL;
    }
    bucket->head = NULL;
    free(bucket->head->key);
    free(bucket->head->value);
    free(bucket->head);
    bucket->size--;
    set->map->size--;
}

int SISMEMBER(Hashset* set, char* elem) {
    int bucketIndex = hashingFunction(elem) % set->map->bucket_count;
    LinkedList* bucket = set->map->buckets[bucketIndex];
    return bucket->size == 1 ? 1 : 0;
}

int SCARD(Hashset* set) {
    return set->map->size;
}



