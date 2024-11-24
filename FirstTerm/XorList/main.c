#include <stdio.h>
#include "xorList.h"

int main()
{

  XORList list = init();
  pushBack(&list, 4);
  pushBack(&list, 5);
  pushBack(&list, 6);

  printList(&list);

  pushFront(&list, 3);
  pushFront(&list, 2);
  pushFront(&list, 1);

  printList(&list);
  release(&list);
  return 0;
}