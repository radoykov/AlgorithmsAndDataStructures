#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CHECK(ptr)                          \
    if (!ptr)                               \
    {                                       \
        printf("Error memory allocation."); \
        exit(1);                            \
    }
#define MAX_ASCII 255
#define MAX_ARR_SIZE 512

typedef struct
{
    int code;
    char *str;
} LZWNode;

LZWNode *createNode(char *str, int code)
{
    LZWNode *node = malloc(sizeof(LZWNode));
    CHECK(node);
    node->code = code;
    node->str = strdup(str);
    return node;
}

void freeAll(LZWNode **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(arr[i]->str);
        free(arr[i]);
    }
    free(arr);
}

int findByStr(LZWNode **arr, int arrSize, char *str)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (strcmp(arr[i]->str, str) == 0)
        {
            return arr[i]->code;
        }
    }
    return -1;
}

char *findByCode(LZWNode **arr, int arrSize, int code)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i]->code == code)
        {
            return arr[i]->str;
        }
    }
    return NULL;
}

void isItStrInStr(LZWNode **arr, int arrSize, char *str)
{
    for (int i = arrSize - 1; i >= 0; i--)
    {
        char *p = strstr(str, arr[i]->str);
        if (p)
        {
            char temp[100];
            strcpy(temp, str);

            char numStr[20] = "";

            *p = '\0';
            sprintf(numStr, "%d", arr[i]->code);
            strcat(str, numStr);
            strcat(str, p + strlen(numStr));
        }
    }
}

void encodeLZW(char *text)
{
    LZWNode **arr = (LZWNode **)malloc(sizeof(LZWNode *) * MAX_ARR_SIZE);
    CHECK(arr);
    int arrSize = 0;
    int currCode = MAX_ASCII + 1;

    char workingStr[100] = "";
    char curr[2] = "";
    for (int i = 0; text[i] != '\0'; i++)
    {
        curr[0] = text[i];
        curr[1] = '\0';

        char combined[100] = "";
        strcpy(combined, workingStr);
        strcat(combined, curr);

        if (findByStr(arr, arrSize, combined) != -1 || strlen(combined) == 1)
        {
            strcpy(workingStr, combined);
        }
        else
        {
            isItStrInStr(arr, arrSize, workingStr);
            printf("%s", workingStr);
            arr[arrSize++] = createNode(combined, currCode++);
            strcpy(workingStr, curr);
        }
    }

    if (strlen(workingStr) > 0)
    {
        isItStrInStr(arr, arrSize, workingStr);
        printf("%s", workingStr);
    }
    freeAll(arr, arrSize);
}

void decodeLZW(const char *text)
{
    LZWNode **arr = (LZWNode **)malloc(sizeof(LZWNode *) * MAX_ARR_SIZE);
    CHECK(arr);
    int arrSize = 0;
    int currCode = MAX_ASCII + 1;

    char curr[100] = ""; // for numbers as well
    char workingStr[100] = "";
    char combine[200] = "";

    int flag = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char ch = text[i];
        if (isdigit(ch))
        {
            flag++;
            strncat(curr, &ch, 1);
            if (flag != 3)
            {
            continue;
            }
            flag = 0;
            ch = '\0';
        }
        // else
        int code = atoi(curr);
        char *decoded = (code > MAX_ASCII) ? findByCode(arr, arrSize, code) : NULL;

        if (decoded)
        {
            printf("%s", decoded);

            if (strlen(workingStr) > 0)
            {
                strcpy(combine, workingStr);
                strncat(combine, decoded, 1);

                // Only insert if not already in table
                if (findByStr(arr, arrSize, combine) == -1)
                {
                    arr[arrSize++] = createNode(combine, currCode++);
                }
            }

            strcpy(workingStr, decoded);
        }
        else
        {
            // It’s not a known code — treat as literal
            if (strlen(curr) > 0)
            {
                printf("%s", curr);

                if (strlen(workingStr) > 0)
                {
                    strcpy(combine, workingStr);
                    strcat(combine, curr);

                    if (findByStr(arr, arrSize, combine) == -1)
                    {
                        arr[arrSize++] = createNode(combine, currCode++);
                    }
                }

                strcpy(workingStr, curr);
            }
        }

        // Print current non-digit character

        printf("%c", ch);

        char newEntry[2] = {ch, '\0'};

        if (strlen(workingStr) > 0)
        {
            strcpy(combine, workingStr);
            strcat(combine, newEntry);

            if (findByStr(arr, arrSize, combine) == -1)
            {
                arr[arrSize++] = createNode(combine, currCode++);
            }
        }

        strcpy(workingStr, newEntry);
        curr[0] = '\0';
    }

    freeAll(arr, arrSize);
}

int main()
{
    char text[] = "ananas";
    encodeLZW(text);
    printf("\n");
    char text2[] = "an256as";
    decodeLZW(text2);

    return 0;
}