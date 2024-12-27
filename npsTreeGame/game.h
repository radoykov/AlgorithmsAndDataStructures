#ifndef GAME_H
#define GAME_H

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
typedef struct item Item;

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

    Item *requirement;
};

struct inventory
{
    Item **items;
    int size;
};

struct item
{
    char name[MAXLINESIZE];
    int count;
};

//declarations of functions

Nps *init_node(char npsText[MAXLINESIZE]);
Player *initPlayerStep(char playerText[MAXLINESIZE]);
void linkPlayerToNps(Nps *nps, Player *player);
void addPlayerNextNps(Player *player, Nps *nps);
void addItemAsRequirement(Player *player, Item *i);
int checkForInventory(Inventory *inv, Item *req);
void play_dialogue(Nps *root, Inventory *inv);
Nps *createDialogue();
Inventory *initInventory();
Item *createItem(char name[MAXLINESIZE], int count);
void addItem(Inventory *inv, Item *item);
Inventory *createInventory();

#endif