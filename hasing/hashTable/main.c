#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

Node *initNode(char *key, int val)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    CHECK(newNode);
    newNode->key = key;
    newNode->val = val;
    newNode->next = NULL;

    return newNode;
}

HashMap *initHashMap()
{
    HashMap *newMap = (HashMap *)malloc(sizeof(HashMap));
    CHECK(newMap);
    newMap->array = (Node **)calloc(HASH_MAP_SIZE, sizeof(Node *));
    CHECK(newMap->array);

    return newMap;
}

// abv
// a + b + v
int hash(char *key)
{
    int value = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        value += key[i];
    }

    return value;
}

void set(HashMap *hashMap, char *key, int val)
{

    int index = hash(key) % HASH_MAP_SIZE;

    if (hashMap->array[index])
    {
        Node *curr = hashMap->array[index];

        while (curr->next)
        {
            if (!strcmp(key, curr->key))
            {
                curr->val = val;
                return;
            }
            curr = curr->next;
        }

        curr->next = initNode(key, val);
    }
    else
    {
        hashMap->array[index] = initNode(key, val);
    }
}

int get(HashMap *hashMap, char *key)
{
    int index = hash(key) % HASH_MAP_SIZE;

    if (hashMap->array[index])
    {
        Node *curr = hashMap->array[index];

        while (curr)
        {
            if (!strcmp(key, curr->key))
            {
                return curr->val;
            }
            curr = curr->next;
        }
    }

    return -1;
}

void printHashMap(HashMap *hashMap)
{
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        if (hashMap->array[i])
        {
            Node *curr = hashMap->array[i];
            printf("[%d]: ", i);
            while (curr)
            {
                printf("%s %d, ", curr->key, curr->val);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

void freeHashMap(HashMap *hashMap)
{
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        Node *curr = hashMap->array[i];
        while (curr)
        {
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    free(hashMap->array);
    free(hashMap);
}

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