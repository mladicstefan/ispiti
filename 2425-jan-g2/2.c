#include <stdio.h>
#include <string.h>

int hexToDek(char c)
{
    if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
        return c - 'a' + 10;
    else if (c >= 0 && c <= '9')
        return c - '0';
    return -1;
}

int main()
{
    char s[255];
    fgets(s, sizeof(s), stdin);
    strtok(s, "\n");
    for (int i = 0; s[i]; i += 2)
    {
        int r1 = hexToDek(s[i]);
        int r2 = hexToDek(s[i + 1]);
        printf("%c", r1 * 16 + r2);
    }
    printf("\n");
    return 0;
}
