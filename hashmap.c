#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_COUNT 256
#define PRIME_NUM 3411949


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

Hashmap* createHashmap() {
    LinkedList** bucketsArr = malloc(BUCKET_COUNT * sizeof(LinkedList*));
    for (int i = 0; i < BUCKET_COUNT; i++) {
        bucketsArr[i] = malloc(sizeof(LinkedList));
        bucketsArr[i]->head = NULL;
        bucketsArr[i]->size = 0;
    }
    Hashmap* map = malloc(sizeof(Hashmap));
    map->buckets = bucketsArr;
    map->size = BUCKET_COUNT;
    return map;
}

long hashingFunction(char* s) {
    long hash = 0;
    while (*s != '\0') {
        hash = PRIME_NUM * hash + *s++;
    }
    return hash < 0 ? -hash : hash; // Ensure positive hash value
}

void insert(Hashmap* map, char* key, char* value) {
    int bucketIndex = hashingFunction(key) % BUCKET_COUNT;
    LinkedList* bucket = map->buckets[bucketIndex];
    Node* n = bucket->head;
    while (n) { //Update value if the key already exists
        if (strcmp(n->key, key) == 0) {
            n->value = value;
            return;
        }
        n = n->next;
    }
    n = malloc(sizeof(Node));
    n->key = key;
    n->value = value;
    n->next = bucket->head;
    bucket->head = n;
    bucket->size += 1;
}

char* get(Hashmap* map, char* key) {
    int bucketIndex = hashingFunction(key) % BUCKET_COUNT;
    LinkedList* bucket = map->buckets[bucketIndex];
    Node* n = bucket->head;
    while (n) {
        if (strcmp(key, n->key) == 0) {
            return n->value;
        }
        n = n->next;
    }
    return NULL;
}

int main(void) {
    Hashmap* map = createHashmap();
    insert(map, "Other Name", "Jason");
    char* s = get(map, "Other Name");
    printf("%s", s);
    return 0;
}
