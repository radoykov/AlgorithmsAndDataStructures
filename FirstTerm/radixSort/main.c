//Alexander Radoykov 10V #4

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIGITSCOUNT 10
#define CHECK(p)                            \
    if (p == NULL)                          \
    {                                       \
        printf("\nError alocating memory"); \
        exit(1);                            \
    }

void radixSortRecursion(int *arr, unsigned int count, int depth);
int getMaxValue(int arr[], int size);
int getDigit(int num, int digitPosition);
void radixSort(int *arr, unsigned int count);
int getDigitCount(int num);
void printfArr(int arr[], int size);
void test(int *arr, int count);

int main()
{
    int len = 0;
    // Test #1 All kind of numbers
    int arr[] = {-5, 23, 45, 22, -43, -10, 0, 0, 4785, 5, 22, -55, -155, 125};
    len = sizeof(arr) / sizeof(arr[0]);
    test(arr, len);

    // Test #2 Only negative numbers
    int arr2[] = {-5, -23, -45, -43, -10};
    len = sizeof(arr2) / sizeof(arr2[0]);
    test(arr2, len);

    // Test #3 Only positive numbers
    int arr3[] = {5654, 23, 13, 445, 23, 30};
    len = sizeof(arr3) / sizeof(arr3[0]);
    test(arr3, len);

    // Test #4 Single value array
    int arr4[] = {0};
    len = sizeof(arr4) / sizeof(arr4[0]);
    test(arr4, len);

    return 0;
}

int getMaxValue(int arr[], int size)
{
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int getDigit(int num, int digitPosition)
{
    return (num / (int)pow(10, digitPosition)) % 10;
}

int getDigitCount(int num)
{
    if (num == 0)
        return 1;
    int a = 0;
    while (num != 0)
    {
        num = num / 10;
        a++;
    }

    return a;
}

void radixSort(int *arr, unsigned int count) //O(n * log2(n))
{
    int *arrPositive = (int *)malloc(sizeof(int));
    int *arrNegative = (int *)malloc(sizeof(int));

    unsigned int arrPositiveSize = 0;
    unsigned int arrNegativeSize = 0;

    for (int i = 0; i < count; i++)
    {
        if (arr[i] >= 0)
        {
            arrPositive[arrPositiveSize] = arr[i];
            arrPositiveSize++;

            arrPositive = (int *)realloc(arrPositive, (arrPositiveSize + 1) * sizeof(int));
            CHECK(arrPositive)
        }
        else
        {
            arrNegative[arrNegativeSize] = arr[i] * -1;
            arrNegativeSize++;

            arrNegative = (int *)realloc(arrNegative, (arrNegativeSize + 1) * sizeof(int));
            CHECK(arrNegative)
        }
    }

    if (arrPositiveSize > 0)
    {
        int maxValue = getMaxValue(arrPositive, arrPositiveSize);
        int digitCount = getDigitCount(maxValue);

        radixSortRecursion(arrPositive, arrPositiveSize, digitCount - 1);
    }

    if (arrNegativeSize > 0)
    {
        int maxValue = getMaxValue(arrNegative, arrNegativeSize);
        int digitCount = getDigitCount(maxValue);

        radixSortRecursion(arrNegative, arrNegativeSize, digitCount - 1);
    }

    int index = 0;

    for (int i = arrNegativeSize; i > 0; i--)
    {
        arr[index] = arrNegative[i - 1] * -1;
        index++;
    }

    for (int i = 0; i < arrPositiveSize; i++)
    {
        arr[index] = arrPositive[i];
        index++;
    }
    free(arrPositive);
    free(arrNegative);
}

void radixSortRecursion(int *arr, unsigned int count, int depth)
{

    int *matrix[DIGITSCOUNT] = {NULL}; // declare arr of 10 pointers for all digits (bukets)
    int matrixLen[DIGITSCOUNT] = {0};  // array holds count of numbers in each bucket

    // fill the buckets
    for (int i = 0; i < count; i++)
    {
        int radix = getDigit(arr[i], depth);
        if (matrixLen[radix] != 0)
        {
            matrix[radix] = (int *)realloc(matrix[radix], sizeof(int) * (matrixLen[radix] + 1));
            CHECK(matrix[radix])
        }
        else
        {
            matrix[radix] = (int *)calloc(1, sizeof(int));
            CHECK(matrix[radix])
        }
        matrixLen[radix]++;

        matrix[radix][matrixLen[radix] - 1] = arr[i];
    }
    // recursion
    for (int i = 0; i < DIGITSCOUNT; i++)
    {
        if (matrixLen[i] > 1 && depth > 0)
        {
            radixSortRecursion(matrix[i], matrixLen[i], depth - 1);
        }
    }

    // read buckets and fill sorted numbers back
    int resultCount = count;
    for (int r = DIGITSCOUNT - 1; r >= 0; r--)
    {
        for (int Size = matrixLen[r] - 1; Size >= 0; Size--)
        {
            arr[resultCount - 1] = matrix[r][Size];
            resultCount--;
        }
    }

    for (int i = 0; i < DIGITSCOUNT - 1; i++)
    {
        free(matrix[i]);
    }
}

void printfArr(int arr[], int size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d, ", arr[i]);
    }
}

void test(int *arr, int count)
{
    printf("\n before:");
    printfArr(arr, count);

    radixSort(arr, count);

    printf("\n after:");
    printfArr(arr, count);
    printf("\n");
}
