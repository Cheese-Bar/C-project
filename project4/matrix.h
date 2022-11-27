typedef struct matrix
{
    size_t col;
    size_t row;
    float *data;
} MATRIX;

MATRIX *createMatrix(int row, int col, float *data);

MATRIX *create_random_Matrix(int row, int col);

MATRIX *matmul_plain(MATRIX *a, MATRIX *b);

MATRIX *matmul_improved(MATRIX *a, MATRIX *b);

MATRIX *matmul_openblas(MATRIX *m1, MATRIX *m2);

void printMatrix(MATRIX *const m);
