#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../../DataStructures/Hashset.h" // Assuming the hashset implementation is in "Hashset.h"

#define NUM_ITERATIONS 20
#define LINE_INTERVAL 20

void measureSADDPerformance(Hashset* set, char** elements, int numElements) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        clock_t start = clock();
        for (int i = 0; i < numElements; i++) {
            SADD(set, elements[i]);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average SADD time for %d elements over %d runs: %f seconds\n", numElements, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numElements;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

void measureSREMPerformance(Hashset* set, char** elements, int numElements) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        clock_t start = clock();
        for (int i = 0; i < numElements; i++) {
            SREM(set, elements[i]);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average SREM time for %d elements over %d runs: %f seconds\n", numElements, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numElements;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

void measureSISMEMBERPerformance(Hashset* set, char** elements, int numElements) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        clock_t start = clock();
        for (int i = 0; i < numElements; i++) {
            SISMEMBER(set, elements[i]);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average SISMEMBER time for %d elements over %d runs: %f seconds\n", numElements, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numElements;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

void measureSCARDPerformance(Hashset* set) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        clock_t start = clock();
        SCARD(set);
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average SCARD time over %d runs: %f seconds\n", NUM_ITERATIONS, avg_time);
    double time_per_op = avg_time * 1000000.0;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

char** readWordsFromFile(const char* filename, int* numWords) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char** words = malloc(sizeof(char*) * 600000); // assuming max 600k words if only every tenth word is stored
    char buffer[256];
    int count = 0;
    int lineNumber = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove newline character
        if (lineNumber % LINE_INTERVAL == 0) {
            words[count] = strdup(buffer);
            count++;
        }
        lineNumber++;
    }

    fclose(file);
    *numWords = count;
    return words;
}

int main() {
    Hashset* set = createHashset();
    int numWords;
    char** words = readWordsFromFile("../words.txt", &numWords);

    measureSADDPerformance(set, words, numWords);
    measureSISMEMBERPerformance(set, words, numWords);
    measureSCARDPerformance(set);
    measureSREMPerformance(set, words, numWords);

    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    free(words);
    freeHashset(set);
    return 0;
}
