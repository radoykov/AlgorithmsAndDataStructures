#include <stdio.h>
#include <stdlib.h>

void mergeSort(int arr[], int size);
void merge(int arr1[], int arr2[], int size1, int size2, int merged[]);
void printfArr(int arr[], int len);
void swap(int *a, int *b);

int main()
{
    int arr[] = {1, -9, 10, 5, 8, 23, -3};
    int len = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, len);
    printfArr(arr, len);

    return 0;
}

void merge(int arr1[], int arr2[], int size1, int size2, int merged[])
{
    int *buffer = (int *)malloc((size1 + size2) * sizeof(int));

    int i = 0,
        j = 0, k = 0;
    while (i < size1 && j < size2)
    {
        if (arr1[i] <= arr2[j]) // stable algorithm (=)- do not swap to equal numbers
        {
            buffer[k++] = arr1[i++];
        }
        else
        {
            buffer[k++] = arr2[j++];
        }
    }
    while (i < size1)
    {
        buffer[k++] = arr1[i++];
    }
    while (j < size2)
    {
        buffer[k++] = arr2[j++];
    }

    for (int i = 0; i < size1 + size2; i++)
    {
        merged[i] = buffer[i];
    }
    free(buffer);
}
void mergeSort(int arr[], int size) //O(size * log2(size))
{
    if (size <= 1)
    {
        return;
    }
    int mid = size / 2;
    int *right = arr + mid;
    int *left = arr;

    mergeSort(left, mid);
    mergeSort(right, size - mid);

    merge(left, right, mid, size - mid, arr);
    // printfArr(left, mid);
    // printfArr(right, size - mid);
    // printf("\n-------");
}

void printfArr(int arr[], int len)
{
    printf("\n");

    for (int i = 0; i < len; i++)
    {
        printf("%d, ", arr[i]);
    }
}

void swap(int *a, int *b)
{
    // int c  = *a;
    // *a = *b;
    // *b = c;

    // *a = *a + *b;
    // *b = *a - *b;
    // *a = *a - *b;

    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}