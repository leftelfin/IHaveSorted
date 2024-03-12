#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n)
{
    clock_t start_time = clock(); // Record the start time
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    clock_t end_time = clock(); // Record the end time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    FILE *file = fopen("insertion_sorted.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.");
        exit(1);
    }
    // Write sorted values to insertion_sorted.txt along with time taken
    for (i = 0; i < n; i++)
    {
        fprintf(file, "%d\n", arr[i]);
    }
    fprintf(file, "Time taken for sorting: %.6f seconds", time_taken);
    fclose(file);
}

int main()
{
    FILE *file = fopen("random_numbers.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.");
        exit(1);
    }
    int n = 0, num;
    // Count the number of integers in the file
    while (fscanf(file, "%d", &num) != EOF)
    {
        n++;
    }
    // Move file pointer back to the beginning
    rewind(file);
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }
    int i = 0;
    // Read values from random_numbers.txt
    while (fscanf(file, "%d", &arr[i]) != EOF)
    {
        i++;
    }
    fclose(file);
    // Apply insertion sort
    insertionSort(arr, n);
    free(arr);
    return 0;
}
