#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter rod length: ");
    scanf("%d", &n);
    int *p = malloc((n + 1) * sizeof(int));
    printf("Enter prices for lengths 1..%d: ", n);
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);

    int *r = malloc((n + 1) * sizeof(int));
    int *cut = malloc((n + 1) * sizeof(int));
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        r[j] = INT_MIN;
        for (int i = 1; i <= j; i++) {
            if (p[i] + r[j - i] > r[j]) {
                r[j] = p[i] + r[j - i];
                cut[j] = i;
            }
        }
    }

    printf("Maximum revenue: %d\n", r[n]);
    printf("Pieces:");
    for (int len = n; len > 0; len -= cut[len]) printf(" %d", cut[len]);
    printf("\n");

    free(p); free(r); free(cut);
    return 0;
}