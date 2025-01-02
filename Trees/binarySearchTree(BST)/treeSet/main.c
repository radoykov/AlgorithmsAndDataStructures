#include <stdio.h>
#include "treeSet.h"

int main()
{
    TreeNode *myTreeSet = initTreeNode(5);

    treeSetAdd(myTreeSet, 5);
    treeSetAdd(myTreeSet, 3);
    treeSetAdd(myTreeSet, 4);
    treeSetAdd(myTreeSet, 1);
    treeSetAdd(myTreeSet, 1);
    printf("%d\n", treeSetHeight(myTreeSet));
    treeSetAdd(myTreeSet, 0);
    printf("%d\n", treeSetHeight(myTreeSet));
    printTreeSet(myTreeSet);
    // OR
    //  treeSetAdd2(&myTreeSet, 5);
    //  treeSetAdd2(&myTreeSet, 3);
    //  treeSetAdd2(&myTreeSet, 4);
    //  treeSetAdd2(&myTreeSet, 1);
    //  treeSetAdd2(&myTreeSet, 1);
    //  printTreeSet(myTreeSet);
}