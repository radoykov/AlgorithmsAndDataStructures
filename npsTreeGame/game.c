#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

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
    player->requirement = NULL;
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

void addItemAsRequirement(Player *player, Item *i)
{
    player->requirement = i;
}

int checkForInventory(Inventory *inv, Item *req)
{
    if (req == NULL)
    {
        return 1;
    }
    for (int i = 0; i < inv->size; i++)
    {
        if (strcmp(inv->items[i]->name, req->name) == 0)
        {
            if (inv->items[i]->count >= req->count)
            {
                inv->items[i]->count -= req->count;
                return 1;
            }
            break;
        }
    }
    return 0;
}

void play_dialogue(Nps *root, Inventory *inv)
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
        play_dialogue(root->nextNPS, inv);
        return;
    }
    else if (root->answersCount == 1)
    {
        printf("\nChoose between : ");
        printf("\nThe only possible answer(automaticaly choosen): %s", root->answers[0]->playerLine);
        play_dialogue(root->answers[0]->next, inv);
        return;
    }
    // basic case
    else
    {
        printf("\nChoose between : \n");
        for (int i = 0; i < root->answersCount; i++)
        {
            printf("(%d)%s", i + 1, root->answers[i]->playerLine);
            if (root->answers[i]->requirement != NULL)
            {
                printf(" req:%s %d ", root->answers[i]->requirement->name, root->answers[i]->requirement->count);
            }
            printf("\n");
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
        // inventory check

        if (checkForInventory(inv, root->answers[choice - 1]->requirement) != 1)
        {
            printf("\nYou don't have enoght items.");

            play_dialogue(root, inv);
        }

        play_dialogue(root->answers[choice - 1]->next, inv);

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
    for (int i = 0; i < npsLines; i++)
    {

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
        int npsParentNumber = 0, itemCount = 0;
        char text[MAXLINESIZE], itemText[MAXLINESIZE];

        scanf("\n%d %[^\n]s", &npsParentNumber, &text);
        scanf("\n%d %[^\n]s", &itemCount, &itemText);

        Player *newPlayer = initPlayerStep(text);
        if (itemCount > 0)
        {
            Item *item = createItem(itemText, itemCount);
            addItemAsRequirement(newPlayer, item);
        }
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
    free(parents);

    return root;
}

Inventory *initInventory()
{
    Inventory *i = (Inventory *)malloc(sizeof(initInventory));
    CHECK(i);
    i->items = NULL;
    i->size = 0;

    return i;
}

Item *createItem(char name[MAXLINESIZE], int count)
{

    Item *item = (Item *)malloc(sizeof(Item));
    CHECK(item);

    strcpy(item->name, name);
    item->count = count;

    return item;
}

void addItem(Inventory *inv, Item *item)
{
    if (inv->size == 0)
    {
        inv->items = (Item **)malloc(sizeof(Item *));
        CHECK(inv->items);
    }
    else
    {
        inv->items = (Item **)realloc(inv->items, sizeof(Item) * (inv->size + 1));
        CHECK(inv->items);
    }

    inv->size++;

    inv->items[inv->size - 1] = item;
}

Inventory *createInventory()
{
    Inventory *inv = initInventory();

    int itemsCount = 0;
    printf("\nHow many things do you need: ");
    scanf("\n%d", &itemsCount);

    for (int i = 0; i < itemsCount; i++)
    {
        int count;
        char name[MAXLINESIZE];
        scanf("\n%d %[^\n]s", &count, &name);

        Item *item = createItem(name, count);
        addItem(inv, item);
    }
    return inv;
}
void freePlayer(Player *player)
{
    if (player)
    {
        free(player);
    }
}

void freeTree(Nps *root)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0; i < root->answersCount; i++)
    {
        freeTree(root->answers[i]->next);
        freePlayer(root->answers[i]);
    }
    free(root->answers);
    free(root);
}

void freeInventory(Inventory *inv)
{
    if (inv)
    {
        for (int i = 0; i < inv->size; i++)
        {
            free(inv->items[i]);
        }
        free(inv->items);
        free(inv);
    }
}