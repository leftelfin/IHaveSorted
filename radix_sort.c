#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to get the maximum value in arr[]
int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// Function to perform counting sort of arr[] based on the digit represented by exp
void countSort(int arr[], int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % 10]++;
    }

    // Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

// Function to perform radix sort of arr[]
void radixSort(int arr[], int n)
{
    int max = getMax(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        countSort(arr, n, exp);
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
    // Apply radix sort
    radixSort(arr, n);
    clock_t end_time = clock(); // Record the end time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    FILE *output_file = fopen("radix_sorted.txt", "w");
    if (output_file == NULL)
    {
        printf("Error opening file.");
        exit(1);
    }
    // Write sorted values to radix_sorted.txt along with time taken
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "%d\n", arr[i]);
    }
    fprintf(output_file, "Time taken for sorting: %.6f seconds", time_taken);
    fclose(output_file);

    free(arr);
    return 0;
}
