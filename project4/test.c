#include <stdio.h>
#include "matrix.h"
#include<sys/time.h>

int main(int argc, char const *argv[])
{
    int Narray[9] = {16,128,256,512,1024,2048,4096, 8192, 64*1024};
    for (size_t i = 0; i < 9; i++)
    {   
        int N = Narray[i];

        printf("\nTest for Matrix %d x %d\n", N, N);
        MATRIX *A = create_random_Matrix(N, N);
        MATRIX *B = create_random_Matrix(N, N);

        struct timeval start;
        struct timeval end;
        unsigned long diff;

        // gettimeofday(&start, NULL);
        // matmul_plain(A,B);
        // gettimeofday(&end, NULL);
        // diff = 1e6 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
        // printf("matmul_plain time:%ldus \n", diff);


        // gettimeofday(&start, NULL);
        // matmul_improved(A,B);
        // gettimeofday(&end, NULL);
        // diff = 1e6 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
        // printf("matmul_improved time:%ldus \n",diff);

        gettimeofday(&start, NULL);
        matmul_openblas(A,B);
        gettimeofday(&end, NULL);
        diff = 1e6 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
        printf("matmul_openblas time:%ldus \n", diff);
    }

    return 0;
}
