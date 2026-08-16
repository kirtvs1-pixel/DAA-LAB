#include <stdio.h>

#define MAX 64

/*
 * Special-pattern matrix:
 *
 * A = | A1  A2 |
 *     | A2  A1 |
 *
 * B = | B1  B2 |
 *     | B2  B1 |
 *
 * Product:
 *
 * C = | C1  C2 |
 *     | C2  C1 |
 *
 * C1 = A1*B1 + A2*B2
 * C2 = A1*B2 + A2*B1
 *
 * The input matrices must actually follow this special structure.
 */

void add(int n, int A[MAX][MAX], int B[MAX][MAX],
         int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void specialMultiply(int n,
                     int A[MAX][MAX],
                     int B[MAX][MAX],
                     int C[MAX][MAX]) {

    /* Base case */
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A1[MAX][MAX], A2[MAX][MAX];
    int B1[MAX][MAX], B2[MAX][MAX];

    int P1[MAX][MAX], P2[MAX][MAX];
    int P3[MAX][MAX], P4[MAX][MAX];

    int C1[MAX][MAX], C2[MAX][MAX];

    /* Extract the two unique blocks */
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    /* C1 = A1*B1 + A2*B2 */
    specialMultiply(k, A1, B1, P1);
    specialMultiply(k, A2, B2, P2);
    add(k, P1, P2, C1);

    /* C2 = A1*B2 + A2*B1 */
    specialMultiply(k, A1, B2, P3);
    specialMultiply(k, A2, B1, P4);
    add(k, P3, P4, C2);

    /* Construct C = | C1 C2 |
     *                | C2 C1 |
     */
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C1[i][j];
            C[i][j + k] = C2[i][j];
            C[i + k][j] = C2[i][j];
            C[i + k][j + k] = C1[i][j];
        }
    }
}

int main(void) {
    int n;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX] = {0};

    printf("Enter n (power of 2): ");
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

    specialMultiply(n, A, B, C);

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
T(n) = 4T(n/2) + O(n^2)
     = O(n^2)

Space Complexity:
O(n^2) auxiliary storage in this implementation.
*/