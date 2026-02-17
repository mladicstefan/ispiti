#include <math.h>
#include <stdio.h>
#include <string.h>

int binToInt(char *c)
{
    int res = 0;
    for (int i = 7; i >= 0; i--)
    {
        if (*(c + i) == '1')
        {
            res += pow(2, 7 - i);
        }
    }
    return res;
}

int main()
{
    char s[255];
    fgets(s, sizeof(s), stdin);
    int len = strlen(s);
    strtok(s, "\n");
    if (!(len % 8))
    {
        fprintf(stderr, "NA KURCU TE NOSAM AHHAHAHHAHAHA");
        return -1;
    }
    for (int i = 0; i < len; i += 8)
    {
        int c = binToInt(&s[i]);

        if (c != ' ' || (!(c >= 'A' && c <= 'Z') || !(c >= 'a' && c <= 'z')) ||
            !(c >= '0' && c <= '9'))
        {
            fprintf(stderr, "%djebi se", c);
            return -1;
        }
        printf("%c", c);
    }
    printf("\n");
    return 0;
}
