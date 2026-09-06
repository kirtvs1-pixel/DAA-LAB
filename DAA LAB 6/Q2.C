#include <stdio.h>
#include <math.h>

#define MAX 10

// (i) Matrix Addition
void addition(int A[MAX][MAX], int B[MAX][MAX],
              int C[MAX][MAX], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}


// (ii) Matrix Multiplication
void multiplication(int A[MAX][MAX], int B[MAX][MAX],
                    int C[MAX][MAX], int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}


// (iii) Check Zero Matrix
int isZero(int A[MAX][MAX], int n) {

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0)
                return 0;

    return 1;
}


// (iv) Check Symmetric Matrix
int isSymmetric(int A[MAX][MAX], int n) {

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            if (A[i][j] != A[j][i])
                return 0;
        }
    }

    return 1;
}


// (v) Determinant using Gaussian Elimination
double determinant(int A[MAX][MAX], int n) {

    double temp[MAX][MAX];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = A[i][j];

    double det = 1;

    for (int i = 0; i < n; i++) {

        if (temp[i][i] == 0)
            return 0;

        for (int j = i + 1; j < n; j++) {

            double factor = temp[j][i] / temp[i][i];

            for (int k = i; k < n; k++)
                temp[j][k] -= factor * temp[i][k];
        }

        det *= temp[i][i];
    }

    return det;
}


// (vi) In-place Transpose
void transpose(int A[MAX][MAX], int n) {

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}


// Display Matrix
void display(int A[MAX][MAX], int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", A[i][j]);

        printf("\n");
    }
}


int main() {

    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n;

    printf("Enter order of matrix: ");
    scanf("%d", &n);

    printf("Enter Matrix A:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter Matrix B:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);


    // (i) Addition
    addition(A, B, C, n);

    printf("\nMatrix Addition:\n");
    display(C, n);


    // (ii) Multiplication
    multiplication(A, B, C, n);

    printf("\nMatrix Multiplication:\n");
    display(C, n);


    // (iii) Zero Matrix
    if (isZero(A, n))
        printf("\nA is a Zero Matrix");
    else
        printf("\nA is NOT a Zero Matrix");


    // (iv) Symmetric Matrix
    if (isSymmetric(A, n))
        printf("\nA is a Symmetric Matrix");
    else
        printf("\nA is NOT a Symmetric Matrix");


    // (v) Determinant
    printf("\nDeterminant of A = %.2f",
           determinant(A, n));


    // (vi) Transpose
    transpose(A, n);

    printf("\n\nTranspose of A:\n");
    display(A, n);


    return 0;
}