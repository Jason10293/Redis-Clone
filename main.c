#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> // Added for memory management functions
#include <stdbool.h>
#include "DataStructures/Hashmap.h" 
#include "DataStructures/List.h"
#include "DataStructures/Hashset.h"

void toLower(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        s[i] = tolower(s[i]);
    }
}

typedef struct {
    Hashmap** maps;
    int mapCount;
    List** lists;
    int listCount;
    Hashset** sets;
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
        freeHashmap(ds->maps[i]);
    }
    for (int i = 0; i < ds->listCount; i++) {
        freeList(ds->lists[i]); // changed to free each List* directly
    }
    for (int i = 0; i < ds->setCount; i++) {
        freeHashset(ds->sets[i]);
    }
    free(ds->maps);
    free(ds->lists);
    free(ds->sets);
    free(ds);
}

Hashmap* findHashmap(DataStructures* ds, const char* name) {
    for (int i = 0; i < ds->mapCount; i++) {
        if (strcmp(ds->maps[i]->name, name) == 0) {
            return ds->maps[i];
        }
    }
    return NULL;
}

List* findList(DataStructures* ds, const char* name) {
    for (int i = 0; i < ds->listCount; i++) {
        if (strcmp(ds->lists[i]->name, name) == 0) { // changed to ds->lists[i]->name
            return ds->lists[i];
        }
    }
    return NULL;
}

Hashset* findHashset(DataStructures* ds, const char* name) {
    for (int i = 0; i < ds->setCount; i++) {
        if (strcmp(ds->sets[i]->name, name) == 0) {
            return ds->sets[i];
        }
    }
    return NULL;
}

List* addNewList(DataStructures* ds, char* dsName) {
    ds->lists = realloc(ds->lists, (ds->listCount + 1) * sizeof(List*)); // changed to List*
    ds->lists[ds->listCount] = createList(dsName);
    ds->listCount++;
    return ds->lists[ds->listCount - 1];
}

void executeCommand(DataStructures* ds, char** args, int count, bool fromFile, FILE* writeFile) {
    char* cmd = args[0];
    toLower(cmd);
    if (strcmp(cmd, "set") == 0 && count >= 3) {
        char* dsName = args[1];
        char* key = args[2];
        char* value = (count > 3 ? args[3] : NULL);
        Hashmap* namedMap = findHashmap(ds, dsName);
        if (!namedMap) {
            ds->maps = realloc(ds->maps, (ds->mapCount + 1) * sizeof(Hashmap*));
            ds->maps[ds->mapCount] = createHashmap(256, dsName);
            namedMap = ds->maps[ds->mapCount];
            ds->mapCount++;
        }
        int res = insert(namedMap, key, value);
        fprintf(writeFile, "set %s %s %s\n", dsName, key, value);
        if (!fromFile) {
            printf("%s\n", res == 1 ? "Insertion Successful" : "Error Inserting Key and Value");
        }
    } else if (strcmp(cmd, "get") == 0 && count >= 2) {
        char* dsName = args[1];
        char* key = args[2];
        Hashmap* namedMap = findHashmap(ds, dsName);
        if (!namedMap) {
            printf("No hashmap named %s \n", dsName);
        } else {
            char* s = get(namedMap, key);
            printf("%s\n", s ? s : "Key not found");
        }
    } else if (strcmp(cmd, "del") == 0 && count >= 2) {
        char* dsName = args[1];
        char* key = args[2];
        Hashmap* namedMap = findHashmap(ds, dsName);
        if (!namedMap) {
            printf("No hashmap named %s \n", dsName);
            return;
        }
        int res = deleteKey(namedMap, key);
        if (!fromFile) {
            printf("%s\n", res == 1 ? "Key Deleted" : "Error Deleting Key");
            fprintf(writeFile, "del %s %s\n", dsName, key);
        }
    } else if (strcmp(cmd, "exists") == 0 && count >= 2) {
        char* dsName = args[1];
        char* key = args[2];
        Hashmap* namedMap = findHashmap(ds, dsName);
        if (!namedMap) {
            printf("No hashmap named %s \n", dsName);
            return;
        }
        printf("%d\n", exists(namedMap, key));
    } else if (strcmp(cmd, "lpush") == 0 && count >= 2) {
        char* dsName = args[1];
        char* key = args[2];
        List* namedList = findList(ds, dsName);
        if (!namedList) {
            namedList = addNewList(ds, dsName);
        }
        LPUSH(namedList, key);
        if (!fromFile) {
            fprintf(writeFile, "lpush %s %s\n", dsName, key);
        }
    } else if (strcmp(cmd, "rpush") == 0 && count >= 2) {
        char* dsName = args[1];
        char* key = args[2];
        List* namedList = findList(ds, dsName);
        if (!namedList) {
            namedList = addNewList(ds, dsName);
        }
        RPUSH(namedList, key);
        if (!fromFile) {
            fprintf(writeFile, "rpush %s %s\n", dsName, key);
        }
    } else if (strcmp(cmd, "lpop") == 0 && count >= 1) {
        char* dsName = args[1];
        List* namedList = findList(ds, dsName);
        if (!namedList) {
            printf("List is empty\n");
            return;
        }
        char* value = LPOP(namedList);
        if (!fromFile) {
            printf("%s\n", value);
            fprintf(writeFile, "lpop %s\n", dsName);
        }
    } else if (strcmp(cmd, "rpop") == 0 && count >= 1) {
        char* dsName = args[1];
        List* namedList = findList(ds, dsName);
        if (!namedList) {
            printf("List is empty\n");
            return;
        }
        if (!fromFile) {
            printf("%s\n", RPOP(namedList));
            fprintf(writeFile, "rpop %s\n", dsName);
        }

    } else if (strcmp(cmd, "sadd") == 0 && count >= 2) {
        char* dsName = args[1];
        char* key = args[2];
        Hashset* namedSet = findHashset(ds, dsName);
        if (!namedSet) {
            ds->sets = realloc(ds->sets, (ds->setCount + 1) * sizeof(Hashset*));
            ds->sets[ds->setCount] = createHashset(dsName);
            namedSet = ds->sets[ds->setCount];
            ds->setCount++;
        }
        int ans = SADD(namedSet, key);
        if (!fromFile) {
            fprintf(writeFile, "sadd %s %s\n", dsName, key);
        }
    } else if (strcmp(cmd, "srem") == 0 && count >= 2) {
        char* dsName = args[1];
        char* key = args[2];
        Hashset* namedSet = findHashset(ds, dsName);
        if (!namedSet) {
            printf("Error Removing Key\n");
            return;
        }
        int ans = SREM(namedSet, key);
        if (!fromFile) {
            fprintf(writeFile, "srem %s %s\n", dsName, key);
        }
    } else if (strcmp(cmd, "sismember") == 0 && count >= 2) {
        char* dsName = args[1];
        char* key = args[2];
        Hashset* namedSet = findHashset(ds, dsName);
        if (!namedSet) {
            printf("0\n");
            return;
        }
        int ans = SISMEMBER(namedSet, key);
        printf("%d\n", ans);
    } else if (strcmp(cmd, "scard") == 0 && count >= 1) {
        char* dsName = args[1];
        Hashset* namedSet = findHashset(ds, dsName);
        if (!namedSet) {
            printf("0\n");
            return;
        }
        int ans = SCARD(namedSet);
        printf("%d\n", ans);
    } else if (strcmp(cmd, "sinter") == 0 && count >= 2) {
        char* dsName = args[1];
        char* dsName2 = args[2];
        Hashset* namedSet1 = findHashset(ds, dsName);
        Hashset* namedSet2 = findHashset(ds, dsName2);
        if (!namedSet1 || !namedSet2) {
            printf("Error performing intersection\n");
            return;
        }
        Hashset* inter = SINTER(namedSet1, namedSet2);
        freeHashset(inter);
    } else if (strcmp(cmd, "clear") == 0) {
        FILE* f = fopen("text.txt", "w");
        fclose(f);
        printf("Cached data cleared");
    } else {
        printf("Unknown command\n");
    }
}

void parseAndExecute(DataStructures* ds, char* line, bool fromFile, FILE* writeFile) {
    char* args[5] = { 0 }; // up to 4 tokens plus NULL
    int count = 0;
    args[count] = strtok(line, " \t\r\n");
    while (args[count] && count < 4) {
        count++;
        args[count] = strtok(NULL, " \t\r\n");
    }
    if (!args[0]) return; // empty line

    // Check for exit
    if (strcmp(args[0], "exit") == 0) {
        printf("Exited\n");
        exit(0);
    }

    // Pass tokens to executeCommand
    executeCommand(ds, args, count, fromFile, writeFile);
}

int main(int argc, char* argv[]) {
    DataStructures* ds = createDataStructures();
    char line[1024];

    FILE* file = fopen("text.txt", "r+");
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            parseAndExecute(ds, line, true, file);
        }
        printf("Data Loaded\n");
        fseek(file, 0, SEEK_END); // Move to end so new writes append
    }

    while (1) {
        printf("Enter command: ");
        if (!fgets(line, sizeof(line), stdin)) {
            break; // no more input
        }
        parseAndExecute(ds, line, false, file);
    }

    freeDataStructures(ds);
    if (file) fclose(file); // Close after main loop
    return 0;
}