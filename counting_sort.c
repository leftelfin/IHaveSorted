#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform counting sort
void countingSort(int arr[], int n)
{
    int max = arr[0];
    // Find the maximum element in the array
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    // Create a count array to store count of each element
    int *count = (int *)malloc((max + 1) * sizeof(int));
    if (count == NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }

    // Initialize all elements of count array to 0
    for (int i = 0; i <= max; i++)
    {
        count[i] = 0;
    }

    // Store count of each element in count array
    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }

    // Modify the count array to store the position of each element in the sorted array
    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    // Create a temporary array to store sorted output
    int *output = (int *)malloc(n * sizeof(int));
    if (output == NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }

    free(count);
    free(output);
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
    // Apply counting sort
    countingSort(arr, n);
    clock_t end_time = clock(); // Record the end time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    FILE *output_file = fopen("counting_sorted.txt", "w");
    if (output_file == NULL)
    {
        printf("Error opening file.");
        exit(1);
    }
    // Write sorted values to counting_sorted.txt along with time taken
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "%d\n", arr[i]);
    }
    fprintf(output_file, "Time taken for sorting: %.6f seconds", time_taken);
    fclose(output_file);

    free(arr);
    return 0;
}
