#ifndef HASHSET_H
#define HASHSET_H

#include <stdarg.h>
#include <stddef.h>
#include "Hashmap.h"

struct Hashset {
    Hashmap* map;
    char name[256];
};

typedef struct Hashset Hashset;
Hashset* createHashset(char* name);
void freeHashset(Hashset* set);
int SADD(Hashset* set, char* elem);
int SREM(Hashset* set, char* elem);
int SISMEMBER(Hashset* set, char* elem);
Hashset* SINTER(Hashset* set1, Hashset* set2);
int SCARD(Hashset*);
void printHashset(Hashset* set);

#endif
