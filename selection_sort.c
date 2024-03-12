#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n)
{
    clock_t start_time = clock(); // Record the start time
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        // Swap the found minimum element with the first element
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
    clock_t end_time = clock(); // Record the end time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    FILE *file = fopen("selection_sorted.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.");
        exit(1);
    }
    // Write sorted values to selection_sorted.txt along with time taken
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
    // Apply selection sort
    selectionSort(arr, n);
    free(arr);
    return 0;
}
