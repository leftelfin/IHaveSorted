#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to check if the array is sorted
int isSorted(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return 0; // Array is not sorted
        }
    }
    return 1; // Array is sorted
}

// Function to shuffle the array randomly
void shuffle(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = rand() % n;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Function to perform Bogo Sort
void bogoSort(int arr[], int n)
{
    while (!isSorted(arr, n))
    {
        shuffle(arr, n);
    }
}

int main()
{
    FILE *file = fopen("random_numbers.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.");
        return 1;
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
        return 1;
    }
    int i = 0;
    // Read values from random_numbers.txt
    while (fscanf(file, "%d", &arr[i]) != EOF)
    {
        i++;
    }
    fclose(file);

    clock_t start_time = clock(); // Record the start time
    // Apply Bogo Sort
    bogoSort(arr, n);
    clock_t end_time = clock(); // Record the end time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    FILE *output_file = fopen("bogo_sorted.txt", "w");
    if (output_file == NULL)
    {
        printf("Error opening file.");
        return 1;
    }
    // Write sorted values to bogo_sorted.txt along with time taken
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "%d\n", arr[i]);
    }
    fprintf(output_file, "Time taken for sorting: %.6f seconds", time_taken);
    fclose(output_file);

    free(arr);
    return 0;
}
