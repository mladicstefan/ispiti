/*
(12p) Napisati program koji učitava string koji sadrži reči u CamelCase-u i
formira i ispisuje novi string u snake_case-u na sledeći način: ako reč počinje
velikim slovom, prebacuje ga u malo slovo, a zatim svaku narednu spojenu reč
koja počinje velikim slovom razdvaja donjom crtom i opet pretvara u malo slovo.
Ako prva reč u nizu spojenih reči počinje cifrom, cela reč se preskače, a inače
se razdvaja donjom crtom na kraju niza uzastopnih cifara. Simboli koji nisu
slova i cifre smatraju se validnim krajem reči (tj. prvo naredno slovo započinje
novu reč). Upotreba funkcije strtok u ovom zadatku nije dozvoljena. Primer:
Ulaz: If len(GldBrg81km) > 0X10 & deepWater Then:GoToThe_OtherSide
Izlaz: if len(gld_brg_81_km) > 0X10 & deep_water then:go_to_the_other_side
 * */

// If len(GldBrg81km) > 0X10 & deepWater Then:GoToThe_OtherSide

#include <stdio.h>
#include <string.h>
static inline int isUpper(char c) { return c >= 'A' && c <= 'Z'; }
static inline int isLower(char c) { return c >= 'a' && c <= 'z'; }
static inline int isDigit(char c) { return c >= '0' && c <= '9'; }
static inline int isAlpha(char c) { return isUpper(c) || isLower(c); }
static inline int isAlnum(char c) { return isAlpha(c) || isDigit(c); }
static inline void shiftRight(char *s, size_t len, int pos)
{
    for (int i = len; i >= pos; i--)
        s[i + 1] = s[i];
}
static inline char toLower(char c)
{
    if (isUpper(c))
        return c - 'A' + 'a';
    return c;
}

int main()
{
    char buff[255];
    fgets(buff, sizeof(buff), stdin);
    size_t len = strlen(buff);
    buff[len - 1] = '\0';

    int startWord = 1;
    int digitStart = 0;

    for (int i = 0; buff[i]; i++)
    {
        if (!isAlnum(buff[i]))
        {
            int startWord = 1;
            int digitStart = 0;
            continue;
        }
        if (startWord)
        {
            startWord = 0;

            if (isDigit(buff[i]))
            {
                digitStart = 1;
                continue;
            }

            buff[i] = toLower(buff[i]);
            continue;
        }

        if (digitStart)
            continue;

        if (isDigit(buff[i]))
        {
            if (!isDigit(buff[i - 1]))
            {
                shiftRight(buff, strlen(buff), i);
                buff[i] = '_';
                i++;
            }
            continue;
        }

        if (isUpper(buff[i]))
        {
            shiftRight(buff, strlen(buff), i);
            buff[i] = '_';
            buff[i + 1] = toLower(buff[i + 1]);
            i++;
        }
    }
    printf("%s\n", buff);
}
