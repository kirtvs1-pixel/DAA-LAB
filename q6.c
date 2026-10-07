#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define D(i, j) dp[(i) * (n + 1) + (j)]

static int min3(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

int main() {
    char A[1024], B[1024];
    printf("Enter string A: ");
    scanf("%1023s", A);
    printf("Enter string B: ");
    scanf("%1023s", B);
    int m = strlen(A), n = strlen(B);
    int *dp = malloc((m + 1) * (n + 1) * sizeof(int));

    for (int i = 0; i <= m; i++) D(i, 0) = i;
    for (int j = 0; j <= n; j++) D(0, j) = j;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = A[i - 1] == B[j - 1] ? 0 : 1;
            D(i, j) = min3(D(i - 1, j) + 1, D(i, j - 1) + 1, D(i - 1, j - 1) + cost);
        }
    }

    printf("Edit distance: %d\n", D(m, n));

    char *op = malloc(m + n + 1);
    int *ia = malloc((m + n + 1) * sizeof(int));
    int *ja = malloc((m + n + 1) * sizeof(int));
    int k = 0, i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1] && D(i, j) == D(i - 1, j - 1)) {
            op[k] = 'M'; ia[k] = i; ja[k] = j; i--; j--;
        } else if (i > 0 && j > 0 && D(i, j) == D(i - 1, j - 1) + 1) {
            op[k] = 'S'; ia[k] = i; ja[k] = j; i--; j--;
        } else if (i > 0 && D(i, j) == D(i - 1, j) + 1) {
            op[k] = 'D'; ia[k] = i; ja[k] = j; i--;
        } else {
            op[k] = 'I'; ia[k] = i; ja[k] = j; j--;
        }
        k++;
    }

    printf("Traceback:\n");
    for (int t = k - 1; t >= 0; t--) {
        if (op[t] == 'M') printf("Match      %c\n", A[ia[t] - 1]);
        else if (op[t] == 'S') printf("Substitute %c -> %c\n", A[ia[t] - 1], B[ja[t] - 1]);
        else if (op[t] == 'D') printf("Delete     %c\n", A[ia[t] - 1]);
        else printf("Insert     %c\n", B[ja[t] - 1]);
    }

    free(dp); free(op); free(ia); free(ja);
    return 0;
}