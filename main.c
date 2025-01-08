#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> // Added for memory management functions
#include "DataStructures/Hashmap.h" // Ensure correct path
#include "DataStructures/List.h"
#include "DataStructures/Hashset.h"

void toLower(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        s[i] = tolower(s[i]);
    }
}

typedef struct {
    char name[256];
    Hashmap* map;
} NamedHashmap;

typedef struct {
    char name[256];
    List* list;
} NamedList;

typedef struct {
    char name[256];
    Hashset* set;
} NamedHashset;

typedef struct {
    NamedHashmap* maps;
    int mapCount;
    NamedList* lists;
    int listCount;
    NamedHashset* sets;
    int setCount;
} DataStructures;

DataStructures* createDataStructures() {
    DataStructures* ds = (DataStructures*)malloc(sizeof(DataStructures));
    ds->maps = NULL;
    ds->mapCount = 0;
    ds->lists = NULL;
    ds->listCount = 0;
    ds->sets = NULL;
    ds->setCount = 0;
    return ds;
}

void freeDataStructures(DataStructures* ds) {
    for (int i = 0; i < ds->mapCount; i++) {
        freeHashmap(ds->maps[i].map);
    }
    for (int i = 0; i < ds->listCount; i++) {
        freeList(ds->lists[i].list);
    }
    for (int i = 0; i < ds->setCount; i++) {
        freeHashset(ds->sets[i].set);
    }
    free(ds->maps);
    free(ds->lists);
    free(ds->sets);
    free(ds);
}

NamedHashmap* findHashmap(DataStructures* ds, const char* name) {
    for (int i = 0; i < ds->mapCount; i++) {
        if (strcmp(ds->maps[i].name, name) == 0) {
            return &ds->maps[i];
        }
    }
    return NULL;
}

NamedList* findList(DataStructures* ds, const char* name) {
    for (int i = 0; i < ds->listCount; i++) {
        if (strcmp(ds->lists[i].name, name) == 0) {
            return &ds->lists[i];
        }
    }
    return NULL;
}

NamedHashset* findHashset(DataStructures* ds, const char* name) {
    for (int i = 0; i < ds->setCount; i++) {
        if (strcmp(ds->sets[i].name, name) == 0) {
            return &ds->sets[i];
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 1) {
        printf("%s", "Usage: No arguments needed");
        return 1;
    }
    DataStructures* ds = createDataStructures();
    char command[256];
    char dsName[256];
    char key[256];
    char value[256];
    while (1) {
        printf("Enter command: ");
        scanf("%s", command);
        toLower(command);
        if (strcmp(command, "exit") == 0) {
            printf("%s", "Exited");
            break;
        } else if (strcmp(command, "set") == 0) {
            scanf("%s %s %s", dsName, key, value);
            NamedHashmap* namedMap = findHashmap(ds, dsName);
            if (!namedMap) {
                ds->maps = realloc(ds->maps, (ds->mapCount + 1) * sizeof(NamedHashmap));
                strcpy(ds->maps[ds->mapCount].name, dsName);
                ds->maps[ds->mapCount].map = createHashmap(256);
                namedMap = &ds->maps[ds->mapCount];
                ds->mapCount++;
            }
            int res = insert(namedMap->map, key, value);
            printf("%s\n", res == 1 ? "Insertion Successful" : "Error Inserting Key and Value");
        } else if (strcmp(command, "get") == 0) {
            scanf("%s %s", dsName, key);
            NamedHashmap* namedMap = findHashmap(ds, dsName);
            if (!namedMap) {
                printf("Key not found\n");
            } else {
                char* s = get(namedMap->map, key);
                printf("%s\n", s ? s : "Key not found");
            }
        } else if (strcmp(command, "del") == 0) {
            scanf("%s %s", dsName, key);
            NamedHashmap* namedMap = findHashmap(ds, dsName);
            if (!namedMap) {
                printf("Error Deleting Key\n");
            } else {
                int res = deleteKey(namedMap->map, key);
                printf("%s\n", res == 1 ? "Key Deleted" : "Error Deleting Key");
            }
        } else if (strcmp(command, "exists") == 0) {
            scanf("%s %s", dsName, key);
            NamedHashmap* namedMap = findHashmap(ds, dsName);
            if (!namedMap) {
                printf("0\n");
            } else {
                printf("%d\n", exists(namedMap->map, key));
            }
        } else if (strcmp(command, "lpush") == 0) {
            scanf("%s %s", dsName, key);
            NamedList* namedList = findList(ds, dsName);
            if (!namedList) {
                ds->lists = realloc(ds->lists, (ds->listCount + 1) * sizeof(NamedList));
                strcpy(ds->lists[ds->listCount].name, dsName);
                ds->lists[ds->listCount].list = createList();
                namedList = &ds->lists[ds->listCount];
                ds->listCount++;
            }
            LPUSH(namedList->list, key);
            printList(namedList->list);
        } else if (strcmp(command, "rpush") == 0) {
            scanf("%s %s", dsName, key);
            NamedList* namedList = findList(ds, dsName);
            if (!namedList) {
                ds->lists = realloc(ds->lists, (ds->listCount + 1) * sizeof(NamedList));
                strcpy(ds->lists[ds->listCount].name, dsName);
                ds->lists[ds->listCount].list = createList();
                namedList = &ds->lists[ds->listCount];
                ds->listCount++;
            }
            RPUSH(namedList->list, key);
            printList(namedList->list);
        } else if (strcmp(command, "lpop") == 0) {
            scanf("%s", dsName);
            NamedList* namedList = findList(ds, dsName);
            if (!namedList) {
                printf("List is empty\n");
            } else {
                printf("%s\n", LPOP(namedList->list));
                printList(namedList->list);
            }
        } else if (strcmp(command, "rpop") == 0) {
            scanf("%s", dsName);
            NamedList* namedList = findList(ds, dsName);
            if (!namedList) {
                printf("List is empty\n");
            } else {
                printf("%s\n", RPOP(namedList->list));
                printList(namedList->list);
            }
        } else if (strcmp(command, "sadd") == 0) {
            scanf("%s %s", dsName, key);
            NamedHashset* namedSet = findHashset(ds, dsName);
            if (!namedSet) {
                ds->sets = realloc(ds->sets, (ds->setCount + 1) * sizeof(NamedHashset));
                strcpy(ds->sets[ds->setCount].name, dsName);
                ds->sets[ds->setCount].set = createHashset();
                namedSet = &ds->sets[ds->setCount];
                ds->setCount++;
            }
            int ans = SADD(namedSet->set, key);
            printHashset(namedSet->set);
        } else if (strcmp(command, "srem") == 0) {
            scanf("%s %s", dsName, key);
            NamedHashset* namedSet = findHashset(ds, dsName);
            if (!namedSet) {
                printf("Error Removing Key\n");
            } else {
                int ans = SREM(namedSet->set, key);
                printHashset(namedSet->set);
            }
        } else if (strcmp(command, "sismember") == 0) {
            scanf("%s %s", dsName, key);
            NamedHashset* namedSet = findHashset(ds, dsName);
            if (!namedSet) {
                printf("0\n");
            } else {
                int ans = SISMEMBER(namedSet->set, key);
                printf("%d\n", ans);
            }
        } else if (strcmp(command, "scard") == 0) {
            scanf("%s", dsName);
            NamedHashset* namedSet = findHashset(ds, dsName);
            if (!namedSet) {
                printf("0\n");
            } else {
                int ans = SCARD(namedSet->set);
                printf("%d\n", ans);
            }
        } else if (strcmp(command, "sinter") == 0) {
            char dsName2[256];
            scanf("%s %s", dsName, dsName2);
            NamedHashset* namedSet1 = findHashset(ds, dsName);
            NamedHashset* namedSet2 = findHashset(ds, dsName2);
            if (!namedSet1 || !namedSet2) {
                printf("Error performing intersection\n");
            } else {
                Hashset* inter = SINTER(namedSet1->set, namedSet2->set);
                printHashset(inter);
                freeHashset(inter);
            }
        } else {
            printf("Unknown command\n");
        }
    }
    freeDataStructures(ds);
    return 0;
}