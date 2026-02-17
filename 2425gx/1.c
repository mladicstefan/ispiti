#include <stdio.h>

void matRead(int n, int m[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &m[i][j]);
    }
}
void matPrint(int n, int m[n][n])
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

void checkMat(int n, int m[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int h = i; h < n; h++)
            {
                for (int w = j; w < n; w++)
                {
                    int min = 10, max = 0;
                    for (int r = i; r <= h; r++)
                    {
                        for (int q = j; q <= w; q++)
                        {
                            if (m[r][q] < min)
                                min = m[r][q];
                            if (m[r][q] > max)
                                max = m[r][q];
                        }
                    }
                    if (min == h - i + 1 && max == w - j + 1)
                    {
                        for (int r = i; r <= h; r++)
                        {
                            for (int q = j; q <= w; q++)
                                printf("%d ", m[r][q]);
                            printf("\n");
                        }
                        printf("\n");
                    }
                }
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int m[n][n];
    matRead(n, m);
    checkMat(n, m);
}
