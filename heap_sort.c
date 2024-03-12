#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to heapify a subtree rooted with node i which is an index in arr[]
void heapify(int arr[], int n, int i)
{
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // Left child
    int r = 2 * i + 2; // Right child

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
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
    // Apply heap sort
    heapSort(arr, n);
    clock_t end_time = clock(); // Record the end time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    FILE *output_file = fopen("heap_sorted.txt", "w");
    if (output_file == NULL)
    {
        printf("Error opening file.");
        exit(1);
    }
    // Write sorted values to heap_sorted.txt along with time taken
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "%d\n", arr[i]);
    }
    fprintf(output_file, "Time taken for sorting: %.6f seconds", time_taken);
    fclose(output_file);

    free(arr);
    return 0;
}
