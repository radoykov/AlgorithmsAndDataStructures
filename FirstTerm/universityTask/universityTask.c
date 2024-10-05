#include <stdio.h>

int func(int n);


void main()
{
    printf("\n%d", func(4));
    printf("\n%d", func(1));
    printf("\n%d", func(15));
    printf("\n%d", func(3));
    
}

int func(int n)
{
    //n%4=0 => n+2
    //n%4=1 => n+2
    //n%4=2 => n-2
    //n%4=3 => n-2
    return n ^ 2;
    //0100 xor 0010
    //=> 0110
    //0000, 0001, 0010, 0011 
}