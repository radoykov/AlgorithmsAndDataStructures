#ifndef HASHMAP_H
#define HASMAP_H

#define HASH_MAP_SIZE 8
#define CHECK(ptr)                          \
    if (!ptr)                               \
    {                                       \
        printf("Error memory allocation."); \
        exit(1);                            \
    }

typedef struct Node
{
    char *key;
    int val;
    struct Node *next;
} Node;

typedef struct HashMap
{
    Node **array;
} HashMap;

Node *initNode(char *key, int val);
HashMap *initHashMap();
int hash(char *key);
void set(HashMap *hashMap, char *key, int val);
int get(HashMap *hashMap, char *key);
void printHashMap(HashMap *hashMap);
void freeHashMap(HashMap *hashMap);

#endif