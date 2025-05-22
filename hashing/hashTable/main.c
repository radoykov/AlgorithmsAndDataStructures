#include <stdio.h>
#include <stdlib.h>
#include "hashMap.h"

int main()
{
    HashMap *hashMap = initHashMap();

    set(hashMap, "house", 21);
    set(hashMap, "horse", 5);
    set(hashMap, "listen", 5);
    set(hashMap, "silent", 10);

    printf("house hash: %d\n", hash("house") % HASH_MAP_SIZE);
    printf("horse hash: %d\n", hash("horse") % HASH_MAP_SIZE);
    printf("listen hash: %d\n", hash("listen") % HASH_MAP_SIZE);
    printf("silent hash: %d\n", hash("silent") % HASH_MAP_SIZE);

    printf("house is: %d\n", get(hashMap, "house"));
    printf("horse is: %d\n", get(hashMap, "horse"));
    printf("listen is: %d\n", get(hashMap, "listen"));
    printf("silent is: %d\n", get(hashMap, "silent"));

    printHashMap(hashMap);
    freeHashMap(hashMap);
}