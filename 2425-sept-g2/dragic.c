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

static void trim_leading_spaces(char *s)
{
    int i = 0;
    while (s[i] == ' ')
        i++;
    if (i > 0)
    {
        int j = 0;
        while (s[i])
            s[j++] = s[i++];
        s[j] = '\0';
    }
}

static int cmp_node(const Film *a, const Film *b)
{
    int cg = strcmp(a->glumac, b->glumac);
    if (cg != 0)
        return -cg;
    return strcmp(a->naziv, b->naziv);
}

static Film *insert(Film *root, Film *node)
{
    if (!root)
        return node;

    int c = cmp_node(node, root);
    if (c < 0)
        root->levo = insert(root->levo, node);
    else
        root->desno = insert(root->desno, node);

    return root;
}

static int existsFilmActor(Film *root, const char *naziv, int godina,
                           const char *glumac)
{
    if (!root)
        return 0;
    if (root->godina == godina && strcmp(root->naziv, naziv) == 0 &&
        strcmp(root->glumac, glumac) == 0)
        return 1;
    return existsFilmActor(root->levo, naziv, godina, glumac) ||
           existsFilmActor(root->desno, naziv, godina, glumac);
}

static int existsEarlierSame(Film *root, Film *cur, const char *glumac1)
{
    if (!root)
        return 0;
    if (root == cur)
        return 0;

    if (strcmp(root->glumac, glumac1) == 0 &&
        strcmp(root->naziv, cur->naziv) == 0 && root->godina == cur->godina)
    {

        Film tmpA = *root;
        Film tmpB = *cur;
        if (cmp_node(&tmpA, &tmpB) < 0)
            return 1;
    }

    return existsEarlierSame(root->levo, cur, glumac1) ||
           existsEarlierSame(root->desno, cur, glumac1);
}

Film *ucitajFilmove()
{
    FILE *f = fopen("ulaz.txt", "r");
    if (!f)
        return NULL;

    Film *head = NULL;
    char line[512];

    while (fgets(line, sizeof(line), f))
    {
        char *nl = strchr(line, '\n');
        if (nl)
            *nl = '\0';

        char *tok = strtok(line, ",");
        if (!tok)
            continue;
        char naziv[50];
        strncpy(naziv, tok, sizeof(naziv) - 1);
        naziv[sizeof(naziv) - 1] = '\0';

        tok = strtok(NULL, ",");
        if (!tok)
            continue;
        int godina = atoi(tok);

        while ((tok = strtok(NULL, ",")) != NULL)
        {
            trim_leading_spaces(tok);

            Film *node = (Film *)malloc(sizeof(Film));
            if (!node)
            {
                fclose(f);
                return head;
            }

            strcpy(node->naziv, naziv);
            strcpy(node->glumac, tok);
            node->godina = godina;
            node->levo = node->desno = NULL;

            head = insert(head, node);
        }
    }

    fclose(f);
    return head;
}

void ispisi(Film *head)
{
    if (!head)
        return;
    ispisi(head->levo);
    printf("%s, %s, %d\n", head->naziv, head->glumac, head->godina);
    ispisi(head->desno);
}

void zajednicki(Film *head, char *glumac1, char *glumac2)
{
    if (!head)
        return;

    zajednicki(head->levo, glumac1, glumac2);

    if (strcmp(head->glumac, glumac1) == 0)
    {
        if (!existsEarlierSame(head, head, glumac1))
        {
            if (existsFilmActor(head, head->naziv, head->godina, glumac2))
            {
                printf("%s, %s, %s\n", head->naziv, glumac1, glumac2);
            }
        }
    }

    zajednicki(head->desno, glumac1, glumac2);
}

void filterPoGodini(Film *head, int godina)
{
    if (!head)
        return;
    filterPoGodini(head->levo, godina);
    if (head->godina > godina)
    {
        printf("%s, %s, %d\n", head->naziv, head->glumac, head->godina);
    }
    filterPoGodini(head->desno, godina);
}

Film *obrisiStablo(Film *head)
{
    if (!head)
        return NULL;
    obrisiStablo(head->levo);
    obrisiStablo(head->desno);
    free(head);
    return NULL;
}
int main()
{
    Film *h = ucitajFilmove();
    // ispisi(h);
    zajednicki(h, "Leonardo DiCaprio", "Tom Hardy");
    // filterPoGodini(h, 2015);
    h = obrisiStablo(h);
}
