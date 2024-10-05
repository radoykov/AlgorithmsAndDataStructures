#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int len);
void printfArr(int arr[], int len);
void swap(int *a, int *b);

int main()
{
    int arr[] = {1, -9, 10, 5, 8};
    int len = sizeof(arr) / sizeof(arr[0]);
    insertionSort(arr, len);
    printfArr(arr, len);

    // int a = 5;
    // int b = 7;
    // swap(&a, &b);
    // printf("a=%d, b=%d", a, b);
    return 0;
}

void insertionSort(int arr[], int len)
{
    for (int i = 1; i < len; i++)  // 1 -9 10 ; 1 10 -9
    {
        int currNum = arr[i]; 
        int currIndex = i;
        for (int k = i - 1; k >= 0; k--)
        {
            if (arr[k] > currNum)
            {
                swap(&arr[k], &arr[currIndex]);
                currIndex--;
               
            }
            else break;
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