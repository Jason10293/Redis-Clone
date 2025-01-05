#ifndef HASHSET_H
#define HASHSET_H

#include <stdarg.h>
#include <stddef.h>
#include "Hashmap.h"

struct Hashset{
    Hashmap* map;
};

typedef struct Hashset Hashset;
Hashset* createHashset();
void freeHashset(Hashset* set);
void SADD(Hashset* set, char* elem);
void SREM(Hashset* set, char* elem);
int SISMEMBER(Hashset* set, char* elem);
char* SINTER(Hashset* set1, Hashset* set2);
int SCARD(Hashset*);


#endif
