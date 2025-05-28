#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zigZagEncript(char text[], int key)
{
    int arrSize = strlen(text);
    char helperArr[100] = {'\0'};
    strcpy(helperArr, text);

    int index = 0;
    for (int row = 0; row < key; row++)
    {
        int i = row;
        int downStep = 2 * (key - row - 1);
        int upStep = 2 * row;
        int toggle = 0;

        while (i < arrSize)
        {
            text[index++] = helperArr[i];

            // Alternate between down and up steps for middle rows
            if (row == 0 || row == key - 1)
            {
                i += 2 * (key - 1);
            }
            else
            {
                if (toggle % 2 == 0)
                    i += downStep;
                else
                    i += upStep;
                toggle++;
            }
        }
    }
}

void zigZagDecrypt(char text[], int key)
{
    int arrSize = strlen(text);
    char helperArr[100] = {'\0'};
    strcpy(helperArr, text);

    int index = 0;

    for (int row = 0; row < key; row++)
    {
        int i = row;
        int downStep = 2 * (key - row - 1);
        int upStep = 2 * row;
        int toggle = 0;

        while (i < arrSize)
        {
            text[i] = helperArr[index++];

            if (row == 0 || row == key - 1)
            {
                i += 2 * (key - 1);
            }
            else
            {
                if (toggle % 2 == 0)
                    i += downStep;
                else
                    i += upStep;
                toggle++;
            }
        }
    }
}

int main()
{
    char arr[100] = "Happyend!";
    zigZagEncript(arr, 3);
    printf("\n%s", arr);

    char arr2[100] = "Hy!apedpn";
    zigZagDecrypt(arr2, 3);
    printf("\n%s", arr2);


}
// h               y                   !
//     a       p       e          d
//         p                n