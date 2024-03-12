#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Function to implement Quick Sort
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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

    clock_t start_time = clock(); // Record the start time
    // Apply quick sort
    quickSort(arr, 0, n - 1);
    clock_t end_time = clock(); // Record the end time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    FILE *output_file = fopen("quick_sorted.txt", "w");
    if (output_file == NULL)
    {
        printf("Error opening file.");
        exit(1);
    }
    // Write sorted values to quick_sorted.txt along with time taken
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "%d\n", arr[i]);
    }
    fprintf(output_file, "Time taken for sorting: %.6f seconds", time_taken);
    fclose(output_file);

    free(arr);
    return 0;
}
