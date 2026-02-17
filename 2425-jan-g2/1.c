#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int rows, cols;
    int *data;
} matrix_t;

matrix_t *m_create(int rows, int cols)
{
    matrix_t *m = malloc(sizeof(matrix_t));
    m->rows = rows;
    m->cols = cols;
    m->data = calloc(cols * rows, sizeof(int));
    return m;
}

void mtx_destroy(matrix_t *m)
{
    if (!m)
    {
        return;
    }
    if (m->data)
    {
        free(m->data);
    }
    free(m);
}

void mRead(matrix_t *m)
{
    for (int i = 0; i < m->rows * m->cols; i++)
        scanf("%d", &m->data[i]);
}

int checkMat(matrix_t *m)
{
    const int n = 9;
    const int total = 9 * 9;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (m->data[i * m->rows + j] == m->data[i * m->rows + k])
                {
                    return -1;
                }

                if (m->data[j * m->rows + i] == m->data[k * m->rows + i])
                {
                    return -1;
                }
            }
        }
    }
    const int BLOCK_SIZE = 3;

    for (int i = 0; i < n; i += BLOCK_SIZE)
    {
        for (int j = 0; j < n; j += BLOCK_SIZE)
        {
            for (int r = i; r < BLOCK_SIZE; r++)
            {
                for (int q = i + 1; q < BLOCK_SIZE; q++)
                {
                    if (m->data[i] == m->data[q])
                    {
                        return -1;
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{

    const int n = 9;
    matrix_t *m = m_create(n, n);
    mRead(m);
    printf("%d\n", checkMat(m));
    mtx_destroy(m);
    return 0;
}
