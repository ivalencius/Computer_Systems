/*
* Author: Ilan Valencius
* Email: valencig@bc.edu
*/

// Packages
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initializes matrix of size n.
void init(int n, int matrix[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i * n + j] = rand() % 10;
        }
    }
}

// Standard Matrix multiplication.
void multiply_standard(int n, int a[], int b[], int c[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i * n + j] = 0;
            for (int k = 0; k < n; ++k) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}

// Transposes matrix
void transpose(int n, int b[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int tmp = b[i * n + j];
            b[i * n + j] = b[j * n + i];
            b[j * n + i] = tmp;
        }
    }
}

// Multiplies a matrix and a transpose matrix
void multiply_transpose(int n, int a[], int b[], int c[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i * n + j] = 0;
            for (int k = 0; k < n; ++k) {
                c[i * n + j] += a[i * n + k] * b[j * n + k];
            }
        }
    }
}

// Verifies if matrix a = matrix b
int verify(int n, int a[], int b[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(a[i * n + j] != b[i * n + j])
                return 0;
        }
    }
    return 1;
}

// Prints out matrix
void print(int n, int matrix[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ",matrix[i * n + j]);
        }
	putchar('\n');
    }
}

// Takes in value n and runs process on square matrix with size n*n
void run(int n) {
        // Make arrays
    int *a = (int *)malloc(n * n * sizeof(int));
    int *b = (int *)malloc(n * n * sizeof(int));
    int *c1 = (int *)malloc(n * n * sizeof(int));
    int *c2 = (int *)malloc(n * n * sizeof(int));
    // Intialize a,b
    init(n, a);
    init(n, b);
    // Print initial matrices
    /*printf("Matrix A:\n");
    print(n, a);
    printf("\nMatrix B:\n");
    print(n, b);*/
    // Set up clock 1
    clock_t start, end;
    double time_std, time_trans, time_transmult;
    // Multiply standard
    start = clock();
    multiply_standard(n, a, b, c1);
    end = clock();
    time_std = 1000.0 * (((double)(end - start)) / CLOCKS_PER_SEC);
    //printf("\nMatrix c1 (standard multiplication):\n");
    //print(n, c1);
    // Transpose b
    start = clock();
    transpose(n, b);
    end = clock();
    time_trans = 1000.0 * (((double)(end - start)) / CLOCKS_PER_SEC);
    //printf("\nB transposed:\n");
    //print(n, b);
    // Multiply transposed
    start = clock();
    multiply_transpose(n, a, b, c2);
    end = clock();
    time_transmult = 1000.0 * (((double)(end - start)) / CLOCKS_PER_SEC);
    //printf("\nMatrix c2 (transpose multiplication):\n");
    //print(n, c2);
    // Verify if multiplication is correct
    int verified = verify(n, c1, c2);
    if (verified)
        printf("\nCORRECT TRANSPOSE MULTIPLICATION\n");
    else
        printf("\nINCORRECT TRANSPOSE MULTIPLICATION\n");
    // Print execution times
    printf("\n--- EXECUTION TIME FOR MATRIX SIZE %d (MILLISECONDS) ---", n);
    printf("\nStandard multiplication : %f",time_std);
    printf("\nTransposing matrix : %f", time_trans);
    printf("\nTranspose multiplication: %f\n",time_transmult);
    // Free memory
    free(a);
    free(b);
    free(c1);
    free(c2);
}
// Arranges function calls
int main(void) {
    // MATRIX MAX SIZE
    int max = 1024;
    for (int n = 4; n <= max; n*=2)
        run(n);
}
