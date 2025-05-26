#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBER_IN_ASCII_TABLE 255
#define CHECK(ptr)                          \
    if (!ptr)                               \
    {                                       \
        printf("Error memory allocation."); \
        exit(1);                            \
    }

typedef struct LZWNode
{
    int number;
    char *letters;

} LZWNode;

typedef struct Pointers
{
    char *pStrat;
    char *pEnd;
    int val;

} Pointers;

LZWNode **initLZWArray(int num)
{
    LZWNode **arr = (LZWNode **)malloc(sizeof(LZWNode *) * num);
    CHECK(arr);

    return arr;
}

LZWNode *createLZWNode(char *str, int num)
{
    LZWNode *node = (LZWNode *)malloc(sizeof(LZWNode));
    CHECK(node);

    int strLen = strlen(str);
    node->letters = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    CHECK(node->letters);

    strcpy(node->letters, str);
    node->letters[strLen] = '\0';
    node->number = num;

    return node;
}

int searchInTable(LZWNode **arr, int arrSize, char *text)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (!strcmp(arr[i]->letters, text))
        {
            return arr[i]->number;
        }
    }
    return 0;
}

Pointers *searchPartsOfTableInText(LZWNode **arr, int arrSize, char *text)
{
    Pointers *pstruct = (Pointers *)malloc(sizeof(Pointers));
    CHECK(pstruct);

    for (int i = arrSize - 1; i >= 0; i--)
    {
        char *p = strstr(text, arr[i]->letters);
        if (p != NULL)
        {
            pstruct->pStrat = p;
            pstruct->pEnd = pstruct->pStrat + strlen(arr[i]->letters) - 1;
            pstruct->val = arr[i]->number;
            return pstruct;
        }
    }
    return NULL;
}

void encodeLZW(char *text)
{
    LZWNode **arr = initLZWArray(100);
    int arrSize = 0;

    char workingString[100] = {'\0'};
    int workStrSize = 0;
    char curr = '\0';
    int sizeText = strlen(text);

    for (int i = 0; i < sizeText + 1; i++) // for one loop only more so to finish the calcolations
    {
        curr = text[i];

        // is it in the table
        // writing in a table
        if (workStrSize > 1 && searchInTable(arr, arrSize, workingString) == 0)
        {
            // for print
            char new[100];
            strcpy(new, workingString);
            while (1)
            {

                Pointers *p = searchPartsOfTableInText(arr, arrSize, new);
                if (p == NULL)
                {
                    break;
                }

                int lenBefore = p->pStrat - new;
                if (lenBefore < 0)
                    lenBefore = 0;

                char temp[100] = {0};
                strncpy(temp, new, lenBefore);
                temp[lenBefore] = '\0';

                char numStr[10];
                sprintf(numStr, "%d", p->val);
                strcat(temp, numStr);
                strcat(temp, p->pEnd + 1);

                strcpy(new, temp);
                free(p);
            }
            if (new[0] == '\0')
            {
                printf("%s", workingString);
            }
            else
            {
                printf("%s", new);
            }

            LZWNode *node = createLZWNode(workingString, arrSize + MAX_NUMBER_IN_ASCII_TABLE + 1);
            arr[arrSize++] = node;
            workStrSize = 0;
            memset(workingString, '\0', 100);
        }
        // if it is only one letter
        workingString[workStrSize++] = curr;
    }

    for (int i = 0; i < arrSize; i++)
    {
        free(arr[i]->letters);
        free(arr[i]);
    }
    free(arr);
}

void decodeLZW(char text[])
{
    LZWNode **arr = initLZWArray(100);
    int arrSize = 0;

    char workingString[100] = {'\0'};
    int workStrSize = 0;
    char curr = '\0';
    int sizeText = strlen(text);

    for (int i = 0; i < sizeText + 1; i++) // for one loop only more so to finish the calcolations
    {
        curr = text[i];

        // is it in the table

        // writing in a table
        int numW = atoi(workingString);
        if (workStrSize > 1 && searchInTable(arr, arrSize, workingString) == 0)
        {
            // making the table

            if (numW > 255)
            {
                for (int i = 0; i < arrSize; i++)
                {
                    if (arr[i]->number == numW)
                    {
                        printf("%s", arr[i]->letters);
                        break;
                    }
                }
                workStrSize = 0;
                memset(workingString, '\0', 100);
            }
            else if (numW == 0)
            {
                printf("%s", workingString);

                LZWNode *node = createLZWNode(workingString, arrSize + MAX_NUMBER_IN_ASCII_TABLE + 1);
                arr[arrSize++] = node;
                workStrSize = 0;
                memset(workingString, '\0', 100);
            }
        }

        // if it is only one letter
        workingString[workStrSize++] = curr;
    }
    printf("%s", workingString);

    for (int i = 0; i < arrSize; i++)
    {
        free(arr[i]->letters);
        free(arr[i]);
    }
    free(arr);
}

int main()
{
    // char *name = "ABBAABC";
    char *name = "tobeornottobeorbeornot";
    encodeLZW(name);
    char text[100] = "ABBA256C";
    decodeLZW(text);

    return 0;
}