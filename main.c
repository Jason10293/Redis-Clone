#include <stdio.h>
#include <ctype.h>
#include <string.h>


void toLower(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        s[i] = tolower(s[i]);
    }
}
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("%s", "Usage: [GET/SET] [KEY] [VALUE]");
        return 1;
    }
    toLower(argv[1]);
    char* COMMAND = argv[1];
    char* KEY = argv[2];
    char* VALUE = argv[3];

    return 0;
}