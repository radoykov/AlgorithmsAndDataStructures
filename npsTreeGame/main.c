#include <stdio.h>
#include "game.h"

int main()
{
    Inventory *inv = createInventory();
    Nps *root = createDialogue();
    play_dialogue(root, inv);
    freeTree(root);//It work for perfect trees. For npsNode who have special pointer to other npsNode, it will just free all nodes,
    //without this. Although it won't make any problems during the duration of the program.
    freeInventory(inv);
    return 0;
}