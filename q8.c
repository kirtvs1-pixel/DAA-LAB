#include <stdio.h>
#include <stdlib.h>
#include <float.h>

static int n;
static int *root;

#define E(i, j) e[(i) * (n + 1) + (j)]
#define W(i, j) w[(i) * (n + 1) + (j)]
#define R(i, j) root[(i) * (n + 1) + (j)]

void printTree(int i, int j, int parent, const char *side) {
    if (i > j) {
        if (parent == 0) return;
        printf("d%d is the %s child of k%d\n", j, side, parent);
        return;
    }
    int r = R(i, j);
    if (parent == 0) printf("k%d is the root\n", r);
    else printf("k%d is the %s child of k%d\n", r, side, parent);
    printTree(i, r - 1, r, "left");
    printTree(r + 1, j, r, "right");
}

int main() {
    printf("Enter number of keys: ");
    scanf("%d", &n);
    double *p = malloc((n + 1) * sizeof(double));
    double *q = malloc((n + 1) * sizeof(double));
    printf("Enter probabilities p1..p%d: ", n);
    for (int i = 1; i <= n; i++) scanf("%lf", &p[i]);
    printf("Enter probabilities q0..q%d: ", n);
    for (int i = 0; i <= n; i++) scanf("%lf", &q[i]);

    double *e = malloc((n + 2) * (n + 1) * sizeof(double));
    double *w = malloc((n + 2) * (n + 1) * sizeof(double));
    root = malloc((n + 2) * (n + 1) * sizeof(int));

    for (int i = 1; i <= n + 1; i++) {
        E(i, i - 1) = q[i - 1];
        W(i, i - 1) = q[i - 1];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            E(i, j) = DBL_MAX;
            W(i, j) = W(i, j - 1) + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = E(i, r - 1) + E(r + 1, j) + W(i, j);
                if (t < E(i, j)) {
                    E(i, j) = t;
                    R(i, j) = r;
                }
            }
        }
    }

    printf("Minimum expected search cost: %.4f\n", E(1, n));
    printTree(1, n, 0, "");

    free(p); free(q); free(e); free(w); free(root);
    return 0;
}