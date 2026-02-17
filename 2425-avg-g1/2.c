#include <stdio.h>
#include <string.h>

char transformisi_karakter(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    if (c >= 'a' && c <= 'z')
        return c - 32;
    if (c >= '0' && c <= '9')
        return '0' + (10 - (c - '0'));
    return c;
}

void pomeri_udesno(char tekst[], int *duzina, int pozicija)
{
    for (int i = *duzina; i > pozicija; i--)
        tekst[i] = tekst[i - 1];
    (*duzina)++;
}

void obrisi_deo(char tekst[], int *duzina, int pozicija, int koliko)
{
    if (pozicija + koliko > *duzina)
        koliko = *duzina - pozicija;
    for (int i = pozicija; i + koliko <= *duzina; i++)
        tekst[i] = tekst[i + koliko];
    *duzina -= koliko;
}

int main()
{
    char tekst[255];
    fgets(tekst, sizeof(tekst), stdin);
    int duzina = strlen(tekst);
    if (duzina > 0 && tekst[duzina - 1] == '\n')
    {
        tekst[duzina - 1] = '\0';
        duzina--;
    }
    for (int i = 0; i < duzina; i++)
    {
        if (tekst[i] == '+' && i > 0)
        {
            char prethodni = tekst[i - 1];
            pomeri_udesno(tekst, &duzina, i);
            tekst[i] = prethodni;
            tekst[i + 1] = prethodni;
        }
        else if (tekst[i] == '?' && i > 0)
        {
            tekst[i - 1] = transformisi_karakter(tekst[i - 1]);
            obrisi_deo(tekst, &duzina, i, 1);
            i--;
        }
        else if (tekst[i] == '!' && i < duzina - 1)
        {
            obrisi_deo(tekst, &duzina, i, 4);
            i--;
        }
    }
    printf("%s\n", tekst);
    return 0;
}
