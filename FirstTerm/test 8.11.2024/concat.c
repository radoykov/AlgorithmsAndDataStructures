#include <stdio.h>
#include "dLinkedList.h"

Dlist concat(Dlist *list1, Dlist *list2)
{
    if (!list2->size)
    {
        return;
    }
    if (!list1->size)
    {
        list1->head = list2->head;
        list1->tail = list2->tail;
        list1->size = list2->size;
    }
    else
    {
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
        list1->size += list2->size;
    }

    list2->head = NULL;
    list2->tail = NULL;
    list2->size = 0;
}


int main() 
{
    Dlist list1 = initList();
    pushBack(&list1, 1);
    pushBack(&list1, 2);
    pushBack(&list1, 3);
    Dlist list2 = initList();
    pushBack(&list1, 4);
    pushBack(&list1, 5);
    pushBack(&list1, 6);

    concat(&list1, &list2);
    printFromHead(&list1);

    return 0;
}