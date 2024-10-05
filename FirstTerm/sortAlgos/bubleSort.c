#include <stdio.h>
#include <stdlib.h>

void bubleSort(int arr[], int len);
void printfArr(int arr[], int len);
void swap(int *a, int *b);

int main()
{
    int arr[] = {1, -9, 10, 5, 8};
    int len = sizeof(arr) / sizeof(arr[0]);
    bubleSort(arr, len);
    printfArr(arr, len);

    // int a = 5;
    // int b = 7;
    // swap(&a, &b);
    // printf("a=%d, b=%d", a, b);
    return 0;
}

void bubleSort(int arr[], int len)
{
    //int change;//high performance
    for (int i = 0; i < len - 1; i++)
    {
        //change = 0;
        for (int k = 0; k < len - i - 1; k++)
        {
            if(arr[k] > arr[k+1]){
                swap(&arr[k], &arr[k + 1]);
                //change = 1;
            }
        }
        //if(change == 0){break;}
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