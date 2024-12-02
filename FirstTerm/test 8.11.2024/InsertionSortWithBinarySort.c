#include <stdio.h>

void printArr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int binarySearch(int arr[], int size, int value)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (value < arr[mid])
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
        // всички вътрешни за цикъла операции са с константна времева сложност O(1)
    }
    return left;
} // O(logN) защото на всяка итерация делим възможния брой елементи на 2

void insertionSort(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    { // O(N)
        int value = arr[i];
        if (value < arr[i - 1])
        {
            int pos = binarySearch(arr, i, value); // O(logN)
            for (int j = i; j > pos; j--)
            { // O(N)
                arr[j] = arr[j - 1];
            }
            arr[pos] = value;
        } // този блок има цялостна сложност O(N), тъй като O(logN) расте по-бавно като функция

    } // => цялата функция има сложност O(N*N) = O(N^2)
}


void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{
    int arr1[] = {4, 1, 2, 7, 9, 10, 2, 1, 1, 3, 10};
    int arr1sorted[] = {1, 1, 1, 2, 2, 3, 4, 7, 9, 10, 10};
    int size1 = sizeof(arr1sorted) / sizeof(0);

    printf("%d\n", binarySearch(arr1sorted, size1, 11));
    printf("%d\n", binarySearch(arr1sorted, size1, -2));
    printf("Original Array for Variant 1:\n");
    printArr(arr1, size1);
    insertionSort(arr1, size1);
    printf("Sorted Array (Insertion Sort with Binary Search):\n");
    printArr(arr1, size1);

    return 0;
}