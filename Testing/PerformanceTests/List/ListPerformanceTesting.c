#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../../DataStructures/List.h" // Assuming list.h contains the list implementation

#define NUM_ITERATIONS 100
#define LINE_INTERVAL 2
void measureLPUSHPerformance(List *list, char **words, int numWords)
{
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++)
    {
        clock_t start = clock();
        for (int i = 0; i < numWords; i++)
        {
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

void measureRPUSHPerformance(List *list, char **words, int numWords)
{
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++)
    {
        clock_t start = clock();
        for (int i = 0; i < numWords; i++)
        {
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

void measureLPOPPerformance(List *list, int numOperations)
{
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++)
    {
        clock_t start = clock();
        for (int i = 0; i < numOperations; i++)
        {
            char *value = LPOP(list);
            if (value)
            {
                free(value);
            }
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average LPOP time for %d elements over %d runs: %f seconds\n", numOperations, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numOperations;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}

void measureRPOPPerformance(List *list, int numOperations)
{
    double total_time = 0.0;
    for (int j = 0; j < NUM_ITERATIONS; j++)
    {
        clock_t start = clock();
        for (int i = 0; i < numOperations; i++)
        {
            char *value = RPOP(list);
            if (value)
            {
                free(value);
            }
        }
        clock_t end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    double avg_time = total_time / NUM_ITERATIONS;
    printf("Average RPOP time for %d elements over %d runs: %f seconds\n", numOperations, NUM_ITERATIONS, avg_time);
    double time_per_op = (avg_time * 1000000.0) / numOperations;
    printf("Average time in microseconds per operation: %f\n\n", time_per_op);
}
char **readWordsFromFile(const char *filename, int *numWords)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char **words = malloc(sizeof(char *) * 600000); // assuming max 600k words if only every tenth word is stored
    char buffer[256];
    int count = 0;
    int lineNumber = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove newline character
        if (lineNumber % LINE_INTERVAL == 0)
        {
            words[count] = strdup(buffer);
            count++;
        }
        lineNumber++;
    }

    fclose(file);
    *numWords = count;
    return words;
}
int main()
{
    List *list = createList();
    int numWords;
    char **words = readWordsFromFile("words.txt", &numWords);

    measureLPUSHPerformance(list, words, numWords);
    measureLPOPPerformance(list, numWords);
    measureRPUSHPerformance(list, words, numWords);
    measureRPOPPerformance(list, numWords);

    for (int i = 0; i < numWords; i++)
    {
        free(words[i]);
    }
    free(words);
    freeList(list);
    return 0;
}

/*
| **Operation**  | **Number of Elements** | **Average Time (seconds)** | **Average Time per Operation (microseconds)** |
|----------------|------------------------|----------------------------|-----------------------------------------------|
| **LPUSH**      | 15552                  | 0.001330                   | 0.085520                                      |
|                | 31104                  | 0.003405                   | 0.109471                                      |
|                | 46655                  | 0.005280                   | 0.113171                                      |
|                | 93310                  | 0.012850                   | 0.137713                                      |
|                | 155517                 | 0.021150                   | 0.135998                                      |
|                | 466549                 | 0.089635                   | 0.192123                                      |
------------------------------------------------------------------------------------------------------------------------
| **LPOP**       | 15552                  | 0.015425                   | 0.991834                                      |
|                | 31104                  | 0.071345                   | 2.293756                                      |
|                | 46655                  | 0.181610                   | 3.892616                                      |
|                | 93310                  | 0.102635                   | 1.099936                                      |
|                | 155517                 | 0.277090                   | 1.781734                                      |
|                | 466549                 | 1.157240                   | 2.480425                                      |
------------------------------------------------------------------------------------------------------------------------
| **RPUSH**      | 15552                  | 0.004960                   | 0.318930                                      |
|                | 31104                  | 0.019420                   | 0.624357                                      |
|                | 46655                  | 0.019205                   | 0.411639                                      |
|                | 93310                  | 0.013520                   | 0.144893                                      |
|                | 155517                 | 0.020405                   | 0.131208                                      |
|                | 466549                 | 0.139055                   | 0.298050                                      |
------------------------------------------------------------------------------------------------------------------------
| **RPOP**       | 15552                  | 0.015800                   | 1.015947                                      |
|                | 31104                  | 0.045680                   | 1.468621                                      |
|                | 46655                  | 0.083220                   | 1.783732                                      |
|                | 93310                  | 0.100440                   | 1.076412                                      |
|                | 155517                 | 0.229725                   | 1.477170                                      |
|                | 466549                 | 0.447360                   | 0.958870                                      |
------------------------------------------------------------------------------------------------------------------------
*/