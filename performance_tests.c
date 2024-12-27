#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashmap.h"

#define NUM_ITERATIONS 50

void measureInsertionPerformance(Hashmap* map, char** keys, int numOperations) {
    char value[256];
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        clock_t start = clock();
        for (int i = 0; i < numOperations; i++) {
            sprintf(value, "value%d", i);
            insert(map, keys[i], value);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        // Clear the map for the next iteration
        for (int i = 0; i < numOperations; i++) {
            deleteKey(map, keys[i]);
        }
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average insertion time for %d elements over %d runs: %f seconds\n", numOperations, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numOperations;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

void measureRetrievalPerformance(Hashmap* map, char** keys, int numOperations) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        // Insert elements before retrieval
        char value[256];
        for (int i = 0; i < numOperations; i++) {
            sprintf(value, "value%d", i);
            insert(map, keys[i], value);
        }
        clock_t start = clock();
        for (int i = 0; i < numOperations; i++) {
            get(map, keys[i]);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        // Clear the map for the next iteration
        for (int i = 0; i < numOperations; i++) {
            deleteKey(map, keys[i]);
        }
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average retrieval time for %d elements over %d runs: %f seconds\n", numOperations, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numOperations;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

void measureDeletionPerformance(Hashmap* map, char** keys, int numOperations) {
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        // Insert elements before deletion
        char value[256];
        for (int i = 0; i < numOperations; i++) {
            sprintf(value, "value%d", i);
            insert(map, keys[i], value);
        }
        clock_t start = clock();
        for (int i = 0; i < numOperations; i++) {
            deleteKey(map, keys[i]);
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average deletion time for %d elements over %d runs: %f seconds\n", numOperations, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numOperations;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

char** readWordsFromFile(const char* filename, int* numWords) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char** words = malloc(sizeof(char*) * 600000); // assuming max 200k words if only every fifth word is stored
    char buffer[256];
    int count = 0;
    int lineNumber = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove newline character
        if (lineNumber % 5 == 0) { // Only store every fifth word
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
    Hashmap* map = createHashmap(256);
    int numOperations;
    char** keys = readWordsFromFile("words.txt", &numOperations);
    measureInsertionPerformance(map, keys, numOperations);
    measureRetrievalPerformance(map, keys, numOperations);
    measureDeletionPerformance(map, keys, numOperations);

    for (int i = 0; i < numOperations; i++) {
        free(keys[i]);
    }
    free(keys);
    freeHashmap(map);
    return 0;
}


/*
Oeration  |	Element | No Resizing(s) | No Resizing (µs/Op) | w/ Resizing(s)	| w/ Resizing(µs/Op)
Insertion	46,655	    0.108540	       2.326439	            0.051480	        1.103419
Retrieval	46,655	    0.164280	       3.521166	            0.009720	        0.208338
Deletion	46,655	    0.365800	       7.840532	            0.027260	        0.584289
Insertion	93,310	    1.163760	       12.471975	        0.098700	        1.057764
Retrieval	93,310	    1.185340	       12.703247	        0.039640	        0.424820
Deletion	93,310	    0.867500	       9.296967	            0.051560	        0.552567
Insertion	155,517	    3.807540	       24.483111	        0.140900	        0.906010
Retrieval	155,517	    2.310820	       14.858954	        0.034380	        0.221069
Deletion	155,517	    2.061340	       13.254757	        0.093740	        0.602764
*/
