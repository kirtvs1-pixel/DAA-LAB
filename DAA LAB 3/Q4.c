#include <stdio.h>

#define MAX 64

void add(int n, int A[MAX][MAX], int B[MAX][MAX],
         int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[MAX][MAX], int B[MAX][MAX],
              int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[MAX][MAX],
              int B[MAX][MAX], int C[MAX][MAX]) {

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A11[MAX][MAX], A12[MAX][MAX];
    int A21[MAX][MAX], A22[MAX][MAX];

    int B11[MAX][MAX], B12[MAX][MAX];
    int B21[MAX][MAX], B22[MAX][MAX];

    int P1[MAX][MAX], P2[MAX][MAX];
    int P3[MAX][MAX], P4[MAX][MAX];
    int P5[MAX][MAX], P6[MAX][MAX], P7[MAX][MAX];

    int T1[MAX][MAX], T2[MAX][MAX];

    /* Divide matrices into four blocks */
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    /* P1 = A11 * (B12 - B22) */
    subtract(k, B12, B22, T1);
    strassen(k, A11, T1, P1);

    /* P2 = (A11 + A12) * B22 */
    add(k, A11, A12, T1);
    strassen(k, T1, B22, P2);

    /* P3 = (A21 + A22) * B11 */
    add(k, A21, A22, T1);
    strassen(k, T1, B11, P3);

    /* P4 = A22 * (B21 - B11) */
    subtract(k, B21, B11, T1);
    strassen(k, A22, T1, P4);

    /* P5 = (A11 + A22) * (B11 + B22) */
    add(k, A11, A22, T1);
    add(k, B11, B22, T2);
    strassen(k, T1, T2, P5);

    /* P6 = (A12 - A22) * (B21 + B22) */
    subtract(k, A12, A22, T1);
    add(k, B21, B22, T2);
    strassen(k, T1, T2, P6);

    /* P7 = (A11 - A21) * (B11 + B12) */
    subtract(k, A11, A21, T1);
    add(k, B11, B12, T2);
    strassen(k, T1, T2, P7);

    /* C11 = P5 + P4 - P2 + P6 */
    add(k, P5, P4, T1);
    subtract(k, T1, P2, T2);
    add(k, T2, P6, T1);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C[i][j] = T1[i][j];

    /* C12 = P1 + P2 */
    add(k, P1, P2, T1);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C[i][j + k] = T1[i][j];

    /* C21 = P3 + P4 */
    add(k, P3, P4, T1);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C[i + k][j] = T1[i][j];

    /* C22 = P5 + P1 - P3 - P7 */
    add(k, P5, P1, T1);
    subtract(k, T1, P3, T2);
    subtract(k, T2, P7, T1);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C[i + k][j + k] = T1[i][j];
}

int main(void) {
    int n;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX] = {0};

    printf("Enter matrix size n (power of 2): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid matrix size.\n");
        return 0;
    }

    int temp = n;
    while (temp % 2 == 0 && temp > 1)
        temp /= 2;

    if (temp != 1) {
        printf("n must be a power of 2.\n");
        return 0;
    }

    printf("Enter Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassen(n, A, B, C);

    printf("\nResult Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}

/*
Time Complexity:
T(n) = 7T(n/2) + O(n^2)
     = O(n^(log2 7))
     = O(n^2.807)

Space Complexity:
O(n^2) auxiliary storage in this implementation.
*/