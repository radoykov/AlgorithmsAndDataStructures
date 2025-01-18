#include <stdio.h>
#include "redBlackTree.h"

int main()
{   
    Node * root = NULL;
    insert(&root, 12);
    insert(&root, 8);
    insert(&root, 5);
    insert(&root, 4);
    insert(&root, 11);
    insert(&root, 18);
    insert(&root, 17);

    printInOrder(root);
}