#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <omp.h>
#include "OpenBLAS/include/cblas.h"
#include<sys/time.h>

#include <nmmintrin.h>//SSE4.2(include smmintrin.h)
#include <immintrin.h>//AVX(include wmmintrin.h)

MATRIX *createMatrix(int row, int col, float *data)
{
    MATRIX *matrix = NULL;
    if (col <= 0 || row <= 0 || data == NULL)
    {
        printf("init matrix error");
        return NULL;
    }

    matrix = (MATRIX *)malloc(sizeof(MATRIX));
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

    for (size_t i = 0; i < col * row; i++) //深拷贝
    {
        matrix->data[i] = data[i];
    }

    return matrix;
}

MATRIX *create_random_Matrix(int row, int col)
{
    MATRIX *matrix = NULL;
    if (col <= 0 || row <= 0)
    {
        printf("init matrix error");
        return NULL;
    }

    matrix = (MATRIX *)malloc(sizeof(MATRIX));
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

    for (size_t i = 0; i < col * row; i++) //深拷贝
    {
        matrix->data[i] = rand();
    }

    return matrix;
}

MATRIX *matmul_plain(MATRIX *a, MATRIX *b)
{
    if (a == NULL || b == NULL)
    {
        printf("input matrix is NULL!");
        return NULL;
    }

    if (a->col != b->row)
    {
        printf("inconsistant size!");
        return NULL;
    }

    float *result = (float *)calloc(a->row * b->col, sizeof(float));
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

MATRIX *matmul_improved(MATRIX *m1, MATRIX *m2)
{
    int B = 16;
    int CAP = 8;
    
    int N = m1->col;
    float * a = m1->data;
    float * b = m2->data;

    MATRIX* m3 = create_random_Matrix(N,N);

    // #pragma omp parallel for num_threads(2)
    for (int i = 0; i < N; i += B) {
        for (int j = 0; j < N; j += B) {
            for (int k = 0; k < N; k += B) {
                for (int ii = i; ii + CAP <= i+B; ii += CAP) {
                    for (int jj = j; jj + CAP <= j+B; jj += CAP) {
                        __m256 vc0, vc1, vc2, vc3, vc4, vc5, vc6, vc7, vc8, vb;
                        vc0 = _mm256_loadu_ps(&m3->data[ii*N+jj]);
                        vc1 = _mm256_loadu_ps(&m3->data[(ii+1)*N+jj]);
                        vc2 = _mm256_loadu_ps(&m3->data[(ii+2)*N+jj]);
                        vc3 = _mm256_loadu_ps(&m3->data[(ii+3)*N+jj]);
                        vc4 = _mm256_loadu_ps(&m3->data[(ii+4)*N+jj]);
                        vc5 = _mm256_loadu_ps(&m3->data[(ii+5)*N+jj]);
                        vc6 = _mm256_loadu_ps(&m3->data[(ii+6)*N+jj]);
                        vc7 = _mm256_loadu_ps(&m3->data[(ii+7)*N+jj]);

                        for (int kk = k; kk + CAP <= k+B; kk += CAP) {
                            vb = _mm256_loadu_ps(&b[kk*N + jj]);
                            vc0 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[ii*N + kk]), vb, vc0);
                            vc1 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+1)*N + kk]), vb, vc1);
                            vc2 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+2)*N + kk]), vb, vc2);
                            vc3 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+3)*N + kk]), vb, vc3);
                            vc4 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+4)*N + kk]), vb, vc4);
                            vc5 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+5)*N + kk]), vb, vc5);
                            vc6 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+6)*N + kk]), vb, vc6);
                            vc7 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+7)*N + kk]), vb, vc7);

                            vb = _mm256_loadu_ps(&b[(kk+1)*N + jj]);
                            vc0 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[ii*N + kk + 1]), vb, vc0);
                            vc1 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+1)*N + kk + 1]), vb, vc1);
                            vc2 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+2)*N + kk + 1]), vb, vc2);
                            vc3 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+3)*N + kk + 1]), vb, vc3);
                            vc4 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+4)*N + kk + 1]), vb, vc4);
                            vc5 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+5)*N + kk + 1]), vb, vc5);
                            vc6 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+6)*N + kk + 1]), vb, vc6);
                            vc7 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+7)*N + kk + 1]), vb, vc7);

                            vb = _mm256_loadu_ps(&b[(kk+2)*N + jj]);
                            vc0 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[ii*N + kk + 2]), vb, vc0);
                            vc1 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+1)*N + kk + 2]), vb, vc1);
                            vc2 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+2)*N + kk + 2]), vb, vc2);
                            vc3 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+3)*N + kk + 2]), vb, vc3);
                            vc4 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+4)*N + kk + 2]), vb, vc4);
                            vc5 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+5)*N + kk + 2]), vb, vc5);
                            vc6 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+6)*N + kk + 2]), vb, vc6);
                            vc7 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+7)*N + kk + 2]), vb, vc7);

                            vb = _mm256_loadu_ps(&b[(kk+3)*N + jj]);
                            vc0 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[ii*N + kk + 3]), vb, vc0);
                            vc1 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+1)*N + kk + 3]), vb, vc1);
                            vc2 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+2)*N + kk + 3]), vb, vc2);
                            vc3 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+3)*N + kk + 3]), vb, vc3);
                            vc4 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+4)*N + kk + 3]), vb, vc4);
                            vc5 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+5)*N + kk + 3]), vb, vc5);
                            vc6 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+6)*N + kk + 3]), vb, vc6);
                            vc7 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+7)*N + kk + 3]), vb, vc7);

                            vb = _mm256_loadu_ps(&b[(kk+4)*N + jj]);
                            vc0 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[ii*N + kk + 4]), vb, vc0);
                            vc1 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+1)*N + kk + 4]), vb, vc1);
                            vc2 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+2)*N + kk + 4]), vb, vc2);
                            vc3 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+3)*N + kk + 4]), vb, vc3);
                            vc4 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+4)*N + kk + 4]), vb, vc4);
                            vc5 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+5)*N + kk + 4]), vb, vc5);
                            vc6 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+6)*N + kk + 4]), vb, vc6);
                            vc7 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+7)*N + kk + 4]), vb, vc7);

                            vb = _mm256_loadu_ps(&b[(kk+5)*N + jj]);
                            vc0 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[ii*N + kk + 5]), vb, vc0);
                            vc1 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+1)*N + kk + 5]), vb, vc1);
                            vc2 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+2)*N + kk + 5]), vb, vc2);
                            vc3 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+3)*N + kk + 5]), vb, vc3);
                            vc4 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+4)*N + kk + 5]), vb, vc4);
                            vc5 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+5)*N + kk + 5]), vb, vc5);
                            vc6 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+6)*N + kk + 5]), vb, vc6);
                            vc7 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+7)*N + kk + 5]), vb, vc7);

                            vb = _mm256_loadu_ps(&b[(kk+6)*N + jj]);
                            vc0 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[ii*N + kk + 6]), vb, vc0);
                            vc1 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+1)*N + kk + 6]), vb, vc1);
                            vc2 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+2)*N + kk + 6]), vb, vc2);
                            vc3 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+3)*N + kk + 6]), vb, vc3);
                            vc4 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+4)*N + kk + 6]), vb, vc4);
                            vc5 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+5)*N + kk + 6]), vb, vc5);
                            vc6 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+6)*N + kk + 6]), vb, vc6);
                            vc7 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+7)*N + kk + 6]), vb, vc7);

                            vb = _mm256_loadu_ps(&b[(kk+7)*N + jj]);
                            vc0 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[ii*N + kk + 7]), vb, vc0);
                            vc1 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+1)*N + kk + 7]), vb, vc1);
                            vc2 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+2)*N + kk + 7]), vb, vc2);
                            vc3 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+3)*N + kk + 7]), vb, vc3);
                            vc4 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+4)*N + kk + 7]), vb, vc4);
                            vc5 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+5)*N + kk + 7]), vb, vc5);
                            vc6 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+6)*N + kk + 7]), vb, vc6);
                            vc7 = _mm256_fmadd_ps(_mm256_broadcast_ss(&a[(ii+7)*N + kk + 7]), vb, vc7);

                        }
                        _mm256_storeu_ps(&m3->data[ii*N+jj], vc0);
                        _mm256_storeu_ps(&m3->data[(ii+1)*N+jj], vc1);
                        _mm256_storeu_ps(&m3->data[(ii+2)*N+jj], vc2);
                        _mm256_storeu_ps(&m3->data[(ii+3)*N+jj], vc3);
                        _mm256_storeu_ps(&m3->data[(ii+4)*N+jj], vc4);
                        _mm256_storeu_ps(&m3->data[(ii+5)*N+jj], vc5);
                        _mm256_storeu_ps(&m3->data[(ii+6)*N+jj], vc6);
                        _mm256_storeu_ps(&m3->data[(ii+7)*N+jj], vc7);
                    }
                }
            }
        }
    }
}

MATRIX *matmul_openblas(MATRIX *m1, MATRIX *m2)
{
    int N = m1->col;
    MATRIX* result = create_random_Matrix(N,N);
    float * C = result->data;
    cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                N, N, N, 1, m1->data, N, m2->data, N, 0, C, N);
    return result;
}


void printMatrix(MATRIX *const m)
{
    if (m == NULL || m->data == NULL)
    {
        printf("NULL matrix");
        return;
    }

    for (size_t i = 0; i < m->row; i++)
    {
        for (size_t j = 0; j < m->col; j++)
        {
            printf("%f ", m->data[i * m->col + j]);
        }
        printf("\n");
    }
    printf("\n");
}
