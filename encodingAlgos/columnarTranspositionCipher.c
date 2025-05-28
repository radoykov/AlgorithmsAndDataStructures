#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void columnEncrypt(char text[], int key)
{
    int arrSize = strlen(text);
    char helperArr[100] = {'\0'};
    strcpy(helperArr, text);
    int index = 0;

    for (int col = 0; col < key; col++)
    {
        for (int row = 0; row * key + col < arrSize; row++)
        {
            text[index++] = helperArr[row * key + col];
        }
    }
}

void columnDecrypt(char text[], int key)
{
    int arrSize = strlen(text);
    char helperArr[100] = {'\0'};
    strcpy(helperArr, text);

    int rows = (arrSize + key - 1) / key;
    int shortCols = (rows * key) - arrSize;  // last columns with fewer rows
    int index = 0;

    for (int col = 0; col < key; col++)
    {
        int maxRow = rows;
        if (col >= key - shortCols)
        {
            maxRow -= 1; // last few columns are shorter
        }

        for (int row = 0; row < maxRow; row++)
        {
            text[row * key + col] = helperArr[index++];
        }
    }
}

int main()
{
    char arr[100] = "Hello_world!";
    columnEncrypt(arr, 3);
    printf("\n%s", arr);

    char arr2[100] = "Hlwleoodl_r!";
    columnDecrypt(arr2, 3);
    printf("\n%s", arr2);
    return 0;
}
// Hel //Hello_
// lo_
// wor
// ld!

// Hlwleoodl_r!
// Hello_world!
