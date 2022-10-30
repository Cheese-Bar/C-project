typedef struct matrix
{
    int col;
    int row;
    float * data;
} MATRIX;

MATRIX * createMatrix(int row, int col, float * data);

void deleteMatrix(MATRIX * matrix);

MATRIX * copyMatrix(MATRIX * from);

MATRIX * addMatrix(MATRIX * const a, MATRIX * const b);

MATRIX * subtractMatrix(MATRIX * const a, MATRIX * const b);

MATRIX * addScalarToMatrix(float x, MATRIX * m);

MATRIX * subScalarFromMatrix(MATRIX * m, float x);

MATRIX * mulScalarWithMatrix(float x, MATRIX * m);

MATRIX * mulMatrixes(MATRIX * a, MATRIX * b);

float findMaxValue(MATRIX * m);

float findMinValue(MATRIX * m);

void printMatrix(MATRIX * const m);
