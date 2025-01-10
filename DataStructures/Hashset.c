#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include "Hashset.h"
#define DEFAULT_BUCKET_COUNT 256
#define CAPACITY_THRESHHOLD 0.75
Hashset* createHashset(char* name) {
    Hashset* set = malloc(sizeof(Hashset));
    set->map = createHashmap(DEFAULT_BUCKET_COUNT, name);
    strcpy(set->name, name);
    return set;
}

void freeHashset(Hashset* set) {
    freeHashmap(set->map);
    free(set);
}

int SADD(Hashset* set, char* elem) {
    if ((double)set->map->size / set->map->bucket_count >= CAPACITY_THRESHHOLD) {
        set->map = resizeHashmap(set->map);
    }
    int bucketIndex = hashingFunction(elem) % set->map->bucket_count;
    LinkedList* bucket = set->map->buckets[bucketIndex];
    SLL_Node* current = bucket->head;
    while (current != NULL) {
        if (strcmp(current->key, elem) == 0) {
            return 0;
        }
        current = current->next;
    }
    SLL_Node* node = malloc(sizeof(SLL_Node));
    node->key = strdup(elem);
    node->value = NULL;
    node->next = bucket->head;
    bucket->head = node;
    bucket->size++;
    set->map->size++;
    return 1;
}

int SREM(Hashset* set, char* elem) {
    int bucketIndex = hashingFunction(elem) % set->map->bucket_count;
    LinkedList* bucket = set->map->buckets[bucketIndex];
    if (bucket->size != 1) {
        return -1;
    }
    SLL_Node* tmp = bucket->head;
    bucket->head = NULL;
    free(tmp->key);
    free(tmp->value);
    free(tmp);
    bucket->size = 0;
    set->map->size--;
    return 1;
}

int SISMEMBER(Hashset* set, char* elem) {
    int bucketIndex = hashingFunction(elem) % set->map->bucket_count;
    LinkedList* bucket = set->map->buckets[bucketIndex];
    return bucket->size == 1 ? 1 : 0;
}

Hashset* SINTER(Hashset* set1, Hashset* set2) {
    int set1NumBuckets = set1->map->bucket_count;
    int set2NumBuckets = set2->map->bucket_count;
    int minBucketCount = set1NumBuckets;

    if (set1NumBuckets > set2NumBuckets) {
        minBucketCount = set2NumBuckets;
    }

    int size = 0;
    Hashset* inter = malloc(sizeof(Hashset));
    char* interName = malloc(strlen(set1->map->name) + strlen(set2->map->name) + 1);
    interName[0] = '\0';
    strcat(interName, set1->map->name);
    strcat(interName, set2->map->name);
    Hashmap* map = createHashmap(minBucketCount, interName);
    inter->map = map;
    for (int i = 0; i < minBucketCount; i++) {
        if ((set1->map->buckets[i]->head && set2->map->buckets[i]->head)) {
            SADD(inter, strdup(set1->map->buckets[i]->head->key));
        }
    }
    return inter;
}

int SCARD(Hashset* set) {
    return set->map->size;
}

void printHashset(Hashset* set) {
    if (set->map->size == 0) {
        printf("EMPTY SET\n");
    }
    for (int i = 0; i < set->map->bucket_count; i++) {
        LinkedList* bucket = set->map->buckets[i];
        SLL_Node* current = bucket->head;
        while (current != NULL) {
            printf("%s\n", current->key);
            current = current->next;
        }
    }
}

