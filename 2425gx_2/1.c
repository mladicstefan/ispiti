/*
4 4 1 2
4 4 3 5
7 8 9 6
2 3 4 4
*/

/*
5 3.14
7 2 3 4 9
5 4 3 8 1
3 3 3 3 3
5 3 8 3 2
7 5 2 2 2
 * */

#include <float.h>
#include <math.h>
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

void checkMat(int n, int m[n][n], double k)
{
    int bestI, bestJ, bestH, bestW;
    double min = DBL_MAX;
    int bestSize = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int h = i; h < n; h++)
            {
                for (int w = j; w < n; w++)
                {

                    double sum = 0;
                    for (int r = i; r <= h; r++)
                    {
                        for (int q = j; q <= w; q++)
                        {
                            sum += m[r][q];
                        }
                    }

                    int count = (h - i + 1) * (w - j + 1);
                    double avgSum = sum / count;
                    double diff = fabs(k - avgSum);

                    if (diff < min)
                    {
                        min = diff;
                        bestI = i;
                        bestJ = j;
                        bestH = h;
                        bestW = w;
                        bestSize = count;
                    }
                    else if (diff == min)
                    {
                        if (count > bestSize)
                        {
                            min = diff;
                            bestI = i;
                            bestJ = j;
                            bestH = h;
                            bestW = w;
                            bestSize = count;
                        }
                    }
                }
            }
        }
    }

    for (int i = bestI; i <= bestH; i++)
    {
        for (int j = bestJ; j <= bestW; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    double k;
    scanf("%d %lf", &n, &k);
    int m[n][n];
    matRead(n, m);
    checkMat(n, m, k);
}
