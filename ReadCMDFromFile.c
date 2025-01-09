#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int getlenLongestLine(FILE* f) {
    int length = 0;
    int max = -1;
    char c;
    while ((c = fgetc(f)) != EOF) {
        if (c != '\n') {
            length++;
        } else {
            if (length > max) {
                max = length;
            }
            length = 0;
        }
    }
    if (length > max) { // Check the last line if it doesn't end with a newline
        max = length;
    }
    return max;
}

int getLongestWord(FILE* f) {
    int length = 0;
    int max = 0;
    char c;
    while ((c = fgetc(f)) != EOF) {
        if (c != ' ' && c != '\n') {
            length++;
        } else {
            if (length > max) {
                max = length;
            }
            length = 0;
        }
    }
    if (length > max) { // Check the last word if it doesn't end with a space or newline
        max = length;
    }
    return max;
}

int main(void) {
    FILE* file = fopen("text.txt", "r");
    int lenLongestLine = getlenLongestLine(file);
    rewind(file);
    int lenLongestWord = getLongestWord(file);
    rewind(file);
    char line[lenLongestLine * 2];
    char command[lenLongestWord * 2];
    char dsName[lenLongestWord * 2];
    char key[lenLongestWord * 2];
    char value[lenLongestWord * 2];
    while (fgets(line, sizeof(line), file)) {
        command[0] = dsName[0] = key[0] = value[0] = '\0';
        int cmds = sscanf(line, "%s %s %s %s", command, dsName, key, value);
        if (command[0]) {
            printf("%s ", command);
        }
        if (dsName[0]) {
            printf("%s ", dsName);
        }
        if (key[0]) {
            printf("%s ", key);
        }
        if (value[0]) {
            printf("%s ", value);
        }
        printf("\n"); // Ensure each command is printed on a new line
    }
    fclose(file);
    return 0;
}

