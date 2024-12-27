#include <stdio.h>
#include "game.h"

int main()
{
    Inventory *inv = createInventory();
    Nps *root = createDialogue();
    play_dialogue(root, inv);
    return 0;
}