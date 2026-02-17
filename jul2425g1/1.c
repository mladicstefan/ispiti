#include <math.h>
#include <stdio.h>

int brDeljenja(int n)
{
    int count = 0;
    for (int i = 1; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    int n;
    scanf("%d", &n);
    int m[n][n];
    int res[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &m[i][j]);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int max = 0;
            int bestK = 0, bestL = 0;

            for (int l = 0; l < n; l++)
                if (brDeljenja(m[i][l]) > max && l != j)
                {
                    max = brDeljenja(m[i][l]);
                    bestK = i;
                    bestL = l;
                }
            for (int l = 0; l < n; l++)
                if (brDeljenja(m[l][j]) > max && l != i)
                {
                    max = brDeljenja(m[l][j]);
                    bestK = l;
                    bestL = j;
                }
            res[i][j] = m[bestK][bestL];
        }
    }

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }
}
