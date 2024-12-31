#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../DataStructures/list.h" // Assuming list.h contains the list implementation

#define NUM_ITERATIONS 200

void measureLPUSHPerformance(List* list, char** words, int numWords) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        clock_t start = clock();
        for (int i = 0; i < numWords; i++) {
            LPUSH(list, words[i]);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average LPUSH time for %d elements over %d runs: %f seconds\n", numWords, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numWords;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

void measureRPUSHPerformance(List* list, char** words, int numWords) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        clock_t start = clock();
        for (int i = 0; i < numWords; i++) {
            RPUSH(list, words[i]);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average RPUSH time for %d elements over %d runs: %f seconds\n", numWords, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numWords;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

void measureLPOPPerformance(List* list, int numOperations) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        clock_t start = clock();
        for (int i = 0; i < numOperations; i++) {
            LPOP(list);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average LPOP time for %d elements over %d runs: %f seconds\n", numOperations, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numOperations;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

void measureRPOPPerformance(List* list, int numOperations) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        clock_t start = clock();
        for (int i = 0; i < numOperations; i++) {
            RPOP(list);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average RPOP time for %d elements over %d runs: %f seconds\n", numOperations, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numOperations;
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
        if (lineNumber % 10 == 0) {
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
    List* list = createList();
    int numWords;
    char** words = readWordsFromFile("words.txt", &numWords);

    measureLPUSHPerformance(list, words, numWords);
    measureRPUSHPerformance(list, words, numWords);
    measureLPOPPerformance(list, numWords);
    measureRPOPPerformance(list, numWords);

    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    free(words);
    freeList(list);
    return 0;
}
