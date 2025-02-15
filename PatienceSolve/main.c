#include <stdio.h>
#include <stdlib.h>
#include "solitaire.h"

int main()
{
    // DIAMONDS,//red КАРО
    // SPADES,//black ПИКА
    // HEARTS,//red КУПА
    // CLUBS//black Спатия

    Stack *stack_1 = createStack("KD,QS,JH,1C,9D,8H\0");
    Stack *stack_2 = createStack("KS,QH,JC,1D,9S,8S\0");
    Stack *stack_3 = createStack("KH,QC,JS,1S,9H,8C\0");
    Stack *stack_4 = createStack("KC,QD,JD,1H,9C,8D\0");
    Stack *stack_5 = createStack("\0");
    Stack *stack_6 = createStack("\0");

    Stack **arr = malloc(sizeof(Stack *) * NUMBER_PILES);
    CHECK(arr);

    arr[0] = stack_1;
    arr[1] = stack_2;
    arr[2] = stack_3;
    arr[3] = stack_4;
    arr[4] = stack_5;
    arr[5] = stack_6;

    int a = playPatience(arr);
    a == 1 ? printf("\nYes there is a solution!") : printf("\nThere isn't any solution.");
    releaseStacks(arr);
    return 0;
}