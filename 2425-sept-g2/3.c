#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Film
{
    char naziv[50];
    char glumac[30];
    int godina;
    struct Film *levo;
    struct Film *desno;
} Film;

Film *kreirajCvor(char *naziv, int godina, char *glumac)
{
    Film *cvor = malloc(sizeof(Film));
    strcpy(cvor->naziv, naziv);
    cvor->godina = godina;
    strcpy(cvor->glumac, glumac);
    cvor->desno = NULL;
    cvor->levo = NULL;
    return cvor;
}

void trimLeadingSpaces(char *s)
{
    int i = 0;
    while (s[i] == ' ')
        i++;
    if (i > 0)
        strcpy(s, s + i);
}

void dodajCvor(Film **head, Film *novi)
{
    if (!*head)
    {
        *head = novi;
        return;
    }

    int cmp = strcmp(novi->glumac, (*head)->glumac);

    if (cmp > 0)
        dodajCvor(&(*head)->levo, novi);
    else if (cmp < 0)
        dodajCvor(&(*head)->desno, novi);
    else
    {
        if (strcmp(novi->naziv, (*head)->naziv) < 0)
            dodajCvor(&(*head)->levo, novi);
        else
            dodajCvor(&(*head)->desno, novi);
    }
}

Film *ucitajFilmove()
{
    Film *stablo = NULL;
    FILE *f = fopen("./ulaz.txt", "r");
    char buff[200];
    while (fgets(buff, sizeof(buff), f))
    {
        char *naziv = strtok(buff, ",");
        trimLeadingSpaces(naziv);
        int godina = atoi(strtok(NULL, ","));
        char *glumac = strtok(NULL, ",\n");
        while (glumac)
        {
            trimLeadingSpaces(glumac);
            Film *novi = kreirajCvor(naziv, godina, glumac);
            dodajCvor(&stablo, novi);
            glumac = strtok(NULL, ",\n");
        }
    }
    fclose(f);
    return stablo;
}
void ispisi(Film *head)
{
    if (!head)
        return;
    ispisi(head->levo);
    printf("%s,%d,%s\n", head->naziv, head->godina, head->glumac);
    ispisi(head->desno);
}

int postojiUFilmu(Film *root, char *naziv, char *glumac)
{
    if (!root)
        return 0;

    if (strcmp(root->naziv, naziv) == 0 && strcmp(root->glumac, glumac) == 0)
        return 1;

    return postojiUFilmu(root->levo, naziv, glumac) ||
           postojiUFilmu(root->desno, naziv, glumac);
}

void zajednicki(Film *head, char *glumac1, char *glumac2)
{
    static Film *root = NULL;
    if (!root)
        root = head;

    if (!head)
        return;

    zajednicki(head->levo, glumac1, glumac2);
    if (strcmp(head->glumac, glumac1) == 0)
    {
        if (postojiUFilmu(root, head->naziv, glumac2))
            printf("%s,%s,%s\n", head->naziv, glumac1, glumac2);
    }
    zajednicki(head->desno, glumac1, glumac2);
}

void filterPoGodini(Film *head, int godina)
{
    if (!head)
    {
        return;
    }
    filterPoGodini(head->levo, godina);
    if (head->godina > godina)
    {
        printf("%s,%d,%s\n", head->naziv, head->godina, head->glumac);
    }
    filterPoGodini(head->desno, godina);
}
Film *obrisiStablo(Film *head)
{
    if (!head)
    {
        return NULL;
    }
    obrisiStablo(head->levo);
    obrisiStablo(head->desno);
    free(head);
    return NULL;
}

int main(void)
{
    Film *head = ucitajFilmove();
    ispisi(head);
    zajednicki(head, "Leonardo DiCaprio", "Tom Hardy");
    filterPoGodini(head, 2010);
    head = obrisiStablo(head);
    return 0;
}
