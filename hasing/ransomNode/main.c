#include <stdio.h>
#include <stdlib.h>

int canMake(char *ransomNote, char *magazine)
{
    int letterOcurrances[26] = {0};

    for (int i = 0; magazine[i] != '\0'; i++)
    {
        letterOcurrances[magazine[i] - 'a']++;
    }

    for (int i = 0; ransomNote[i] != '\0'; i++)
    {
        if (--letterOcurrances[ransomNote[i] - 'a'] < 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    char *ran1 = "abmor";
    char *mag1 = "romba";

    char *ran2 = "wowf";
    char *mag2 = "what will do?";

    printf("Test 3: %d\n", canMake(ran1, mag1)); 
    printf("Test 4: %d\n", canMake(ran2, mag2)); 
}