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

int recPrintBin(int num)
{
    if (num == 0)
    {
        return 0;
    }
    recPrintBin(num / 2);
    printf("%d", num % 2);
}