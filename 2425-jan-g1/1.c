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
    size_t n = m->rows;
    size_t total = m->rows * m->cols;
    int sum = 0;
    for (int i = 0; i < total; i++)
    {
        sum += m->data[i];
        if (m->data[i] < 1 || m->data[i] > total)
        {
            return -1;
        }

        for (int j = i + 1; j < total; j++)
        {
            if (m->data[i] == m->data[j])
            {
                return -1;
            }
        }
    }

    sum /= n;

    for (int i = 0; i < m->cols; i++)
    {
        int row_sum = 0, col_sum = 0;
        for (int j = 0; j < m->rows; j++)
        {
            row_sum += m->data[i * m->rows + j];
            col_sum += m->data[j * m->rows + i];
        }

        if (row_sum != sum || col_sum != sum)
        {
            return -1;
        }
    }

    int diag_sum = 0, antid_sum = 0;
    for (int i = 0; i < n; i++)
    {
        diag_sum += m->data[i * n + i];
        antid_sum += m->data[n * i + (n - 1 - i)];
    }
    if (diag_sum != sum || antid_sum != sum)
    {
        return -1;
    }

    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    matrix_t *m = m_create(n, n);
    mRead(m);
    printf("%d\n", checkMat(m));
    mtx_destroy(m);
    return 0;
}
