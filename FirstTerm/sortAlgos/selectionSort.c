#include <stdio.h>
#include <stdlib.h>

void selectionSort(int arr[], int len);
void printfArr(int arr[], int len);
void swap(int *a, int *b);

int main()
{
    int arr[] = {1, -9, 10, 5, 8};
    int len = sizeof(arr) / sizeof(arr[0]);
    selectionSort(arr, len);
    printfArr(arr, len);

    // int a = 5;
    // int b = 7;
    // swap(&a, &b);
    // printf("a=%d, b=%d", a, b);
    return 0;
}

void selectionSort(int arr[], int len) //O(len^2)
{
    int change;
    for (int i = 0; i < len - 1; i++)
    {
        change = 0;
        int minORmax = arr[i];
        int indexminORmax = i;
        for (int k = i + 1; k < len; k++)
        {
            if (minORmax > arr[k])
            {
                minORmax = arr[k];
                indexminORmax = k;
                change = 1;
            }
        }
        if (change == 1 && indexminORmax != i)
        {
            swap(&arr[i], &arr[indexminORmax]);
        }
    }
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