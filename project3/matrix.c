#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

MATRIX * createMatrix(int row, int col, float * data)
{
    MATRIX* matrix = NULL;
    if (col <= 0 || row <= 0 || data == NULL)
    {
        printf("init matrix error");
        return NULL;
    }

    matrix = (MATRIX*)malloc(sizeof(MATRIX));
    if (matrix == NULL)
    {
        printf("fail to allocate memory to meta matrix");
    }

    matrix->col = col;
    matrix->row = row;
    matrix->data = (float *)calloc(col * row, sizeof(float));
    if (matrix->data == NULL)
    {
        free(matrix);
        matrix = NULL;
        printf("fail to allocate memory to matrix data");
    }

    // matrix->data = data; // 浅拷贝

    for (size_t i = 0; i < col * row; i++)  //深拷贝
    {
        matrix->data[i] = data[i];
    }
    
    return matrix;
}

void deleteMatrix(MATRIX * matrix)
{
    if (matrix == NULL)
    {
        printf("already NULL!");
        return;
    }

    if (matrix->data != NULL)
    {
        free(matrix->data);
        matrix->data = NULL;
    }

    free(matrix);
    matrix = NULL;
}

MATRIX * copyMatrix(MATRIX * from)
{
    if (from == NULL)
    {
        printf("source matrix is NULL!");
        return NULL;
    }
    
    return createMatrix(from->row, from->col, from->data);
}

MATRIX * addMatrix(MATRIX * const a, MATRIX * const b)
{
    if (a==NULL || b == NULL)
    {
        printf("input matrix is NULL!");
        return NULL;
    }

    if (a->row != b ->row || a ->col != b->col)
    {
        printf("inconsistant size!");
        return NULL;
    }

    float * result = (float *)calloc(a->col * a->row, sizeof(float));
    for (size_t i = 0; i < a->col * a->row; i++)
    {
        result[i] = a->data[i] + b->data[i];
    }
    
    return createMatrix(a->row, a->col, result);
}

MATRIX * subtractMatrix(MATRIX * const a, MATRIX * const b)
{
    if (a==NULL || b == NULL)
    {
        printf("input matrix is NULL!");
        return NULL;
    }

    if (a->row != b ->row || a ->col != b->col)
    {
        printf("inconsistant size!");
        return NULL;
    }

    float * result = (float *)calloc(a->col * a->row, sizeof(float));
    for (size_t i = 0; i < a->col * a->row; i++)
    {
        result[i] = a->data[i] - b->data[i];
    }
    
    return createMatrix(a->row, a->col, result);
}

MATRIX * addScalarToMatrix(float x, MATRIX * m)
{
    if (m == NULL || m->data == NULL)
    {
        printf("matrix is NULL!");
        return NULL;
    }

    float * result = (float *)calloc(m->col * m->row, sizeof(float));
    for (size_t i = 0; i < m->col * m->row; i++)
    {
        result[i] = x + m->data[i];
    }

    return createMatrix(m->row, m->col, result);
}

MATRIX * subScalarFromMatrix(MATRIX * m, float x)
{
    if (m == NULL || m->data == NULL)
    {
        printf("matrix is NULL!");
        return NULL;
    }

    float * result = (float *)calloc(m->col * m->row, sizeof(float));
    for (size_t i = 0; i < m->col * m->row; i++)
    {
        result[i] = m->data[i] - x;
    }

    return createMatrix(m->row, m->col, result);
}

MATRIX * mulScalarWithMatrix(float x, MATRIX * m)
{
    if (m == NULL || m->data == NULL)
    {
        printf("matrix is NULL!");
        return NULL;
    }

    float * result = (float *)calloc(m->col * m->row, sizeof(float));
    for (size_t i = 0; i < m->col * m->row; i++)
    {
        result[i] = m->data[i] * x;
    }

    return createMatrix(m->row, m->col, result);
}

MATRIX * mulMatrixes(MATRIX * a, MATRIX * b)
{
    if (a==NULL || b == NULL)
    {
        printf("input matrix is NULL!");
        return NULL;
    }

    if (a->col != b ->row)
    {
        printf("inconsistant size!");
        return NULL;
    }

    float * result = (float *)calloc(a->row * b->col , sizeof(float));
    for (size_t i = 0; i < a->row; i++)
    {
        for (size_t j = 0; j < b->col; j++)
        {
            for (size_t k = 0; k < a->col; k++)
            {            
                result[i * b->col + j] += a->data[i * a->col + k] * b->data[j + k * b->col];
            }
        }
    }
    
    return createMatrix(a->row, b->col, result);

}

float findMaxValue(MATRIX * m)
{
    if (m == NULL || m->data == NULL)
    {
        printf("matrix is NULL!");
        return 0;
    }

    float result = __FLT_MIN__;
    for (size_t i = 0; i < m->col * m->row; i++)
    {
        result = result > m->data[i] ? result : m->data[i];
    }

    return result;
}

float findMinValue(MATRIX * m)
{
    if (m == NULL || m->data == NULL)
    {
        printf("matrix is NULL!");
        return 0;
    }

    float result = __FLT_MAX__;
    for (size_t i = 0; i < m->col * m->row; i++)
    {
        result = result < m->data[i] ? result : m->data[i];
    }

    return result;
}

void printMatrix(MATRIX * const m)
{
    if (m == NULL || m->data==NULL)
    {
        printf("NULL matrix");
        return;
    }

    for (size_t i = 0; i < m->row; i++)
    {
        for (size_t j = 0; j < m->col; j++)
        {
            printf("%f ", m->data[i*m->col + j]);
        }
        printf("\n");
    }
    printf("\n");
}
