#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANDOM_NUMBERS 10000
#define MAX_RANDOM_NUMBER 1000000

int main() {
    int random_numbers[NUM_RANDOM_NUMBERS];
    FILE *file;
    int i, j, temp;

    // Initialize random seed
    srand(time(NULL));

    // Generate random numbers without repetition
    for (i = 0; i < NUM_RANDOM_NUMBERS; ++i) {
        int r = rand() % MAX_RANDOM_NUMBER + 1;
        for (j = 0; j < i; ++j) {
            if (random_numbers[j] == r) {
                // Number already exists, generate a new one
                r = rand() % MAX_RANDOM_NUMBER + 1;
                j = -1; // Restart the loop to check again
            }
        }
        random_numbers[i] = r;
    }

    // Write random numbers to file
    file = fopen("random_numbers.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (i = 0; i < NUM_RANDOM_NUMBERS; ++i) {
        fprintf(file, "%d\n", random_numbers[i]);
    }

    fclose(file);
    printf("Random numbers have been generated and saved to 'random_numbers.txt'.\n");

    return 0;
}
