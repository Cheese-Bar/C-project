#include <stdio.h>
#include "matrix.h"

int main(int argc, char const *argv[])
{
    float a[2 * 3] = {1,2,3,4,5,6};
    float b[3 * 4] = {1,2,3,4,5,6,7,8,9,10,11,12};
    float c[2 * 3] = {1,2,3,4,5,6};
    MATRIX * A = createMatrix(2,3,a);
    MATRIX * B = createMatrix(3,4,b);
    MATRIX * C = createMatrix(2,3,c);

    printf("matrix A: \n");
    printMatrix(A);
    printf("matrix B: \n");
    printMatrix(B);
    printf("matrix C: \n");
    printMatrix(C);

    MATRIX * E = mulMatrixes(A,B);
    printf("matrix A * matrix B: \n");
    printMatrix(E);
    printf("the max value in matrix: \n");
    printf("%f\n", findMaxValue(E));

    MATRIX * F = addMatrix(A,C);
    printf("matrix F = A + C: \n");
    printMatrix(F);

    deleteMatrix(F);
    F = subtractMatrix(A,C);
    printf("matrix F = A - C: \n");
    printMatrix(F);

    MATRIX * D = addScalarToMatrix(100, A);
    printf("matrix D = 100 + A: \n");
    printMatrix(D);

    deleteMatrix(D);
    D = subScalarFromMatrix(A, 100);
    printf("matrix D = A - 100: \n");
    printMatrix(D);

    deleteMatrix(D);
    D = mulScalarWithMatrix(100, A);
    printf("matrix D = A * 100: \n");
    printMatrix(D);

    MATRIX * G = copyMatrix(A);
    printf("matrix G = A: \n");
    printMatrix(G);

    printf("MATRIX A: \n");
    printMatrix(A);
    deleteMatrix(A);
    printf("delete MATRIX A: \n");
    printMatrix(A);

    printf("matrix B: \n");
    printMatrix(B);
    printf("matrix C: \n");
    printMatrix(C);
    printf("B * C: \n");
    mulMatrixes(B,C);

    printf("\n\n");
    printMatrix(NULL);

    printf("\n\n");
    createMatrix(-1,3,a);

    return 0;
}
