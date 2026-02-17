#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    char naslov[50];
    char autor[50];
    int br_strainca;
    float ocena;
    struct node_t *levo, *desno;
} node_t;

node_t *newElement(node_t *stablo, char *naslov, char *autor, int br,
                   float ocena)
{
    stablo = malloc(sizeof(node_t));
    strcpy(stablo->naslov, naslov);
    strcpy(stablo->autor, autor);
    stablo->br_strainca = br;
    stablo->ocena = ocena;
    stablo->desno = NULL;
    stablo->levo = NULL;
    return stablo;
}

node_t *stablo_init()
{
    node_t *stablo = NULL;
    node_t *curr = NULL;

    FILE *f = fopen("./ulaz.txt", "r");
    if (!f)
    {
        fprintf(stderr, "Greska pri ucitavanju fajla %p", f);
        return NULL;
    }

    char lines[100];
    while (fgets(lines, sizeof(lines), f))
    {
        char *naslov = strtok(lines, ",");
        char *autor = strtok(NULL, ",");
        int br_str = atoi(strtok(NULL, ","));
        float ocena = atof(strtok(NULL, "\n"));

        if (!stablo)
            stablo = newElement(stablo, naslov, autor, br_str, ocena);

        else
        {
            curr = newElement(curr, naslov, autor, br_str, ocena);
            node_t *parent = NULL;
            node_t *temp = stablo;

            while (temp)
            {
                parent = temp;
                int cmp = strcmp(curr->naslov, temp->naslov);
                if (cmp < 0)
                    temp = temp->levo;
                else
                    temp = temp->desno;
            }
            int cmp = strcmp(stablo->naslov, curr->naslov);
            if (cmp > 0)
            {
                parent->levo = curr;
            }
            else if (cmp < 0)
            {
                parent->desno = curr;
            }
        }
    }

    fclose(f);
    return stablo;
}

void free_tree(node_t **tree)
{
    if (!(*tree))
    {
        *tree = NULL;
        return;
    }
    free_tree(&(*tree)->desno);
    free_tree(&(*tree)->levo);
    free(*tree);
}

void print_tree(node_t *tree)
{
    if (!tree)
        return;

    print_tree(tree->levo);
    printf("%s, %s, %d, %.1f\n", tree->naslov, tree->autor, tree->br_strainca,
           tree->ocena);
    print_tree(tree->desno);
}

void print_stranice(node_t *tree)
{
    if (!tree)
        return;

    print_tree(tree->levo);
    printf("%s, %s, %d, %.1f\n", tree->naslov, tree->autor, tree->br_strainca,
           tree->ocena);
    print_tree(tree->desno);
}
int main()
{
    node_t *stablo = stablo_init();
    print_tree(stablo);
    free_tree(&stablo);
    return 0;
}
