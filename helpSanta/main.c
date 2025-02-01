#include <stdio.h>
#include <stdlib.h>
#include "helpSanta.h"

int main()
{
    // char *maze = "XXZDC\nXDEAV\nDAXDA\nVDHAX\nBAXXX\n\0";
    // char *solution = helpSanta(maze, 2, 3);
    // printf("%s", solution);

    char *maze = "DHCXDHHCXX\nVXBGEXXVXX\nBCXJCXDAXX\nZFDAVXBGHC\nDEEHFXXVXV\nVXDHFXXBHF\nVXVXBHCXXV\nBHAXXXBHHA\0";
    char *solution = helpSanta(maze, 8, 5);
    printf("%s", solution);
    free(solution);

    return 0;
}
/*
XXZ╔╗
X╔╩╝║
╔╝X╔╝
║╔═╝X <= Santa is above first X , which is in row with 2 others.
╚╝XXX
*/

/*
╔═╗x╔══╗xx
║x╚╦╩xx║xx
╚╗x╠╗x╔╝xx
Z╣╔╝║x╚╦═╗
╔╩╩═╣xx║x║
║x╔═╣xx╚═╣<= Santa is above second X , which is in row with 2 others.
║x║x╚═╗xx║
╚═╝xxx╚══╝
*/
