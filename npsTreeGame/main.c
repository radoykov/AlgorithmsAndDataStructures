#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINESIZE 50
#define CHECK(p)                            \
    if (p == NULL)                          \
    {                                       \
        printf("\nError alocating memory"); \
        exit(1);                            \
    }

typedef struct nps Nps;
typedef struct player Player;
typedef struct inventory Inventory;
typedef struct article Article;

struct nps
{
    char npsLine[MAXLINESIZE];
    int answersCount;
    Player **answers;

    Nps *nextNPS;
};

struct player
{
    char playerLine[MAXLINESIZE];
    Nps *next;
};

struct inventory
{
    Article *inventory;
    int size;
};

struct article
{
    char name[MAXLINESIZE];
    int count;
};

Nps *init_node(char npsText[MAXLINESIZE])
{
    if (npsText == NULL)
    {
        return NULL;
    }

    Nps *nps = (Nps *)malloc(sizeof(Nps));
    CHECK(nps);

    nps->answers = NULL;
    nps->answersCount = 0;
    nps->nextNPS = NULL;
    strcpy(nps->npsLine, npsText);
    return nps;
}

Player *initPlayerStep(char playerText[MAXLINESIZE])
{
    if (playerText == NULL)
    {
        return NULL;
    }

    Player *player = (Player *)malloc(sizeof(Player));
    CHECK(player);

    player->next = NULL;
    strcpy(player->playerLine, playerText);

    return player;
}

void linkPlayerToNps(Nps *nps, Player *player)
{
    if (nps->answersCount == 0)
    {
        nps->answers = (Player **)malloc(sizeof(Player));
        CHECK(nps->answers);
    }
    else
    {
        nps->answers = (Player **)realloc(nps->answers, sizeof(Player) * (nps->answersCount + 1));
        CHECK(nps->answers);
    }
    nps->answersCount++;

    nps->answers[nps->answersCount - 1] = player;
}

void addPlayerNextNps(Player *player, Nps *nps)
{
    player->next = nps;
}

void play_dialogue(Nps *root)
{
    // main check
    if (root != NULL)
    {
        printf("\nnps:%s", root->npsLine);
    }
    else
    {
        printf("\nGame finish.");
        return;
    }
    // diff cases
    if (root->answersCount == 0 && root->nextNPS == NULL)
    {
        printf("\nGame finish.");
        return;
    }
    else if (root->answersCount == 0)
    {
        play_dialogue(root->nextNPS);
        return;
    }
    else if (root->answersCount == 1)
    {
        printf("\nChoose between : ");
        printf("\nThe only possible answer(automaticaly choosen): %s", root->answers[0]->playerLine);
        play_dialogue(root->answers[0]->next);
        return;
    }
    // basic case
    else
    {
        printf("\nChoose between : ");
        for (int i = 0; i < root->answersCount; i++)
        {
            printf("(%d)%s ", i + 1, root->answers[i]->playerLine);
        }
        // validation of input comand about choosen thing
        int choice = 0;
        do
        {
            printf("\nYour choice is: ");

            scanf("%d", &choice);
            if (choice >= 1 && choice <= root->answersCount)
            {
                break;
            }
            printf("Error wrong number. Try again.");

        } while (1);

        play_dialogue(root->answers[choice -1]->next);
        return;
    }
}

Nps *createDialogue()
{
    int npsLines = 0;
    scanf("\n%d", &npsLines);

    Nps **npsList = (Nps **)malloc(sizeof(Nps *) * npsLines);
    CHECK(npsList);

    int *parents = (int *)malloc(sizeof(int) * npsLines);
    CHECK(parents);

    for (int i = 0; i < npsLines; i++)
    {
        int npsParentNumber;
        char text[MAXLINESIZE];

        scanf("\n%d %[^\n]s", &npsParentNumber, &text);

        Nps *newNps = init_node(text);
        npsList[i] = newNps;
        parents[i] = npsParentNumber;

    }
    for (int i = 0; i < npsLines; i++){

        if (parents[i] > 0 && parents[i] <= npsLines)
        {
            npsList[parents[i] - 1]->nextNPS = npsList[i];
        }
    }

    int playerLines = 0;
    scanf("\n%d", &playerLines);

    Player **playerList = (Player **)malloc(sizeof(Player *) * npsLines);
    CHECK(playerList);

    for (int i = 0; i < playerLines; i++)
    {
        int npsParentNumber;
        char text[MAXLINESIZE];

        scanf("\n%d %[^\n]s", &npsParentNumber, &text);

        Player *newPlayer = initPlayerStep(text);
        linkPlayerToNps(npsList[npsParentNumber - 1], newPlayer);

        playerList[i] = newPlayer;
    }
    int neededLinks = 0;
    scanf("\n%d", &neededLinks);

    for (int i = 0; i < neededLinks; i++)
    {
        int nextNps, currPlayer;
        scanf("\n%d %d", &nextNps, &currPlayer);

        addPlayerNextNps(playerList[currPlayer - 1], npsList[nextNps - 1]);
    }

    Nps *root = npsList[0];

    free(npsList);
    free(playerList);

    return root;
}

int main()
{
    Nps *root = createDialogue();
    play_dialogue(root);
    return 0;
}