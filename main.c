#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "DataStructures/hashmap.h" // Ensure correct path
#include "DataStructures/list.h"

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
        } else if (strcmp(command, "LPUSH")) {
            scanf("%s", key);
            LPUSH(list, key);
            printList(list);
        } else {
            printf("Unknown command\n");
        }

    }
    freeHashmap(map);
    return 0;
}