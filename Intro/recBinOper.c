#include <stdio.h>

int recPrintBin(int num);

void main()
{

    recPrintBin(2);
    printf("\n");
    recPrintBin(5);
    printf("\n");
    recPrintBin(25); 
}

int recPrintBin(int num) // O(log2(n))
{
    if (num >> 1) 
    {
        recPrintBin(num >> 1);
    }
    printf("%d", num & 1);
}