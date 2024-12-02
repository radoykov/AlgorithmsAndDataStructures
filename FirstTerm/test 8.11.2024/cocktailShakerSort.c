#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void printArr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void cocktailShakerSort(int arr[], int size)
{
    for (int i = 0; i < size / 2; i++)
    { // O(N/2) = O(N) итерации
        int swapped = 0;
        for (int j = i; j < size - i - 1; j++)
        { // O(N)
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        } // вътрешните операции са константни O(1)
        if (!swapped)
        {
            break;
        }
        swapped = 0;
        for (int j = size - i - 1; j > i; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(&arr[j], &arr[j - 1]);
                swapped = 1;
            }
        }
        if (!swapped)
        {
            break;
        } // втория цикъл е абсолютно аналогичен на първия
    }
} // цялостната функция тогава е със сложност O(N * (N + N)) = O(2N^2) = O(N^2)

int main()
{
    int arr2[] = {3, 8, 7, 6, 5, 4, 2};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("\nOriginal Array for Variant 2:\n");
    printArr(arr2, size2);
    cocktailShakerSort(arr2, size2);
    printf("Sorted Array (Cocktail Shaker Sort):\n");
    printArr(arr2, size2);
}