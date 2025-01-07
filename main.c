#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "DataStructures/Hashmap.h" // Ensure correct path
#include "DataStructures/List.h"
#include "DataStructures/Hashset.h"

void toLower(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        s[i] = tolower(s[i]);
    }
}
int main(int argc, char* argv[]) {
    if (argc != 1) {
        printf("%s", "Usage: No arguments needed");
        return 1;
    }
    Hashmap* map = createHashmap(256);
    List* list = createList();
    Hashset* set = createHashset();
    Hashset* set1 = createHashset();
    char command[256];
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
            scanf("%s %s", key, value);
            int res = insert(map, key, value);
            printf("%s\n", res == 1 ? "Insertion Successful" : "Error Inserting Key and Value");
        } else if (strcmp(command, "get") == 0) {
            scanf("%s", key);
            char* s = get(map, key);
            printf("%s\n", s ? s : "Key not found");
        } else if (strcmp(command, "del") == 0) {
            scanf("%s", key);
            int res = deleteKey(map, key);
            printf("%s\n", res == 1 ? "Key Deleted" : "Error Deleting Key");
        } else if (strcmp(command, "exists") == 0) {
            scanf("%s", key);
            printf("%d\n", exists(map, key));
        } else if (strcmp(command, "lpush") == 0) {
            scanf("%s", key);
            LPUSH(list, key);
            printList(list);
        } else if (strcmp(command, "rpush") == 0) {
            scanf("%s", key);
            RPUSH(list, key);
            printList(list);
        } else if (strcmp(command, "lpop") == 0) {
            printf("%s\n", LPOP(list));
            printList(list);
        } else if (strcmp(command, "rpop") == 0) {
            printf("%s\n", RPOP(list));
            printList(list);
        } else if (strcmp(command, "sadd") == 0) {
            scanf("%s", key);
            int ans = SADD(set, key);
            printHashset(set);
        } else if (strcmp(command, "srem") == 0) {
            scanf("%s", key);
            int ans = SREM(set, key);
            printHashset(set);
        } else if (strcmp(command, "sismember") == 0) {
            scanf("%s", key);
            int ans = SISMEMBER(set, key);
            printf("%d\n", ans);
        } else if (strcmp(command, "scard") == 0) {
            int ans = SCARD(set);
            printf("%d\n", ans);
        } else if (strcmp(command, "sinter") == 0) {
            SADD(set, "a");
            SADD(set, "b");
            SADD(set, "c");
            SADD(set, "d");
            SADD(set1, "z");
            SADD(set1, "z");
            SADD(set1, "z");
            SADD(set1, "z");
            Hashset* inter = SINTER(set, set1);
            printHashset(inter);
        }

        else {
            printf("Unknown command\n");
        }

    }
    freeList(list);
    freeHashmap(map);
    freeHashset(set);
    return 0;
}