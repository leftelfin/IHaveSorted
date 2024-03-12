#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// A structure to represent a node in the bucket
struct Node
{
    int value;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node into the bucket
void insertNode(struct Node **bucket, int value)
{
    struct Node *newNode = createNode(value);
    if (*bucket == NULL)
    {
        *bucket = newNode;
    }
    else
    {
        struct Node *temp = *bucket;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to perform insertion sort on a bucket
void insertionSort(struct Node **bucket)
{
    struct Node *sorted = NULL;
    struct Node *current = *bucket;
    while (current != NULL)
    {
        struct Node *next = current->next;
        if (sorted == NULL || current->value < sorted->value)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            struct Node *temp = sorted;
            while (temp->next != NULL && temp->next->value < current->value)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *bucket = sorted;
}

// Function to perform bucket sort
void bucketSort(int arr[], int n)
{
    // Create empty buckets
    int numBuckets = 10;
    struct Node **buckets = (struct Node **)malloc(numBuckets * sizeof(struct Node *));
    if (buckets == NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }
    for (int i = 0; i < numBuckets; i++)
    {
        buckets[i] = NULL;
    }

    // Insert elements into buckets
    for (int i = 0; i < n; i++)
    {
        int bucketIndex = arr[i] / numBuckets;
        insertNode(&buckets[bucketIndex], arr[i]);
    }

    // Sort individual buckets
    for (int i = 0; i < numBuckets; i++)
    {
        insertionSort(&buckets[i]);
    }

    // Concatenate buckets
    int index = 0;
    for (int i = 0; i < numBuckets; i++)
    {
        struct Node *current = buckets[i];
        while (current != NULL)
        {
            arr[index++] = current->value;
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(buckets);
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
    // Apply bucket sort
    bucketSort(arr, n);
    clock_t end_time = clock(); // Record the end time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    FILE *output_file = fopen("bucket_sorted.txt", "w");
    if (output_file == NULL)
    {
        printf("Error opening file.");
        return 1;
    }
    // Write sorted values to bucket_sorted.txt along with time taken
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "%d\n", arr[i]);
    }
    fprintf(output_file, "Time taken for sorting: %.6f seconds", time_taken);
    fclose(output_file);

    free(arr);
    return 0;
}
