#include <stdio.h>
#include <string.h>

void caesarCript(char arr[], int shift)
{
    int arrLen = strlen(arr);
    for (int i = 0; i < arrLen; i++)
    {
        if ('A' <= arr[i] && arr[i] <= 'Z')
        {
            int border = shift >= 0 ? 'A' : 'Z';
            arr[i] = (arr[i] + shift - border) % 26 + border;
        }

        else if ('a' <= arr[i] && arr[i] <= 'z')
        {
            int border = shift >= 0 ? 'a' : 'z';
            arr[i] = (arr[i] + shift - border) % 26 + border;
        }
    }
}

int main()
{
    char arr[100] = "Hello world!";
    caesarCript(arr, 4);
    printf("\n%s", arr);

    char arr2[100] = "Lipps asvph!";
    caesarCript(arr2, -4);
    printf("\n%s", arr2);

    char arr3[100] = "Welcome!";
    caesarCript(arr3, 0);
    printf("\n%s", arr3);

    return 0;
}