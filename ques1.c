
/*
 * Q1: Put them in Order
 * ----------------------
 * Goal   : Arrange the given functions in increasing order of growth
 *          for sufficiently large n.
 *
 * Idea   : Comparing raw values directly overflows for functions like
 *          3^n and 2^(32n) even for modest n (double overflows around
 *          n = 1024 for base-2 exponents). Instead, we compare
 *          log2(f(n)) for each function. Since log2 is monotonically
 *          increasing, ordering by log2(f(n)) gives the same order as
 *          ordering by f(n), but stays numerically stable for huge n.
 *
 *          log2 formulas used (n large, n > 1):
 *            f1  = n log2 n              -> log2 n + log2(log2 n)
 *            f2  = 12*sqrt(n)            -> log2(12) + 0.5*log2 n
 *            f3  = 1/n                   -> -log2 n
 *            f4  = n^(log2 n)            -> (log2 n)^2
 *            f5  = 100n^2 + 6n           -> ~ log2(100) + 2*log2 n
 *            f6  = n^0.51                -> 0.51*log2 n
 *            f7  = n^2 - 324             -> ~ 2*log2 n
 *            f8  = 50*n^0.5              -> log2(50) + 0.5*log2 n
 *            f9  = 2n^3                  -> 1 + 3*log2 n
 *            f10 = 3^n                   -> n*log2(3)
 *            f11 = 2^(32n)               -> 32n
 *            f12 = log2 n                -> log2(log2 n)
 *
 * Complexity: Evaluating and sorting 12 values -> O(k log k) where
 *             k = number of functions (constant here), i.e. O(1)
 *             for a fixed function set.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    char name[40];
    double log2_value;
} Func;

int cmp(const void *a, const void *b) {
    double diff = ((Func *)a)->log2_value - ((Func *)b)->log2_value;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

int main(void) {
    double n = 1e6;           /* "sufficiently large" n */
    double log2n = log2(n);

    Func f[12];

    strcpy(f[0].name,  "1/n");                 f[0].log2_value  = -log2n;
    strcpy(f[1].name,  "log2(n)");              f[1].log2_value  = log2(log2n);
    strcpy(f[2].name,  "50*sqrt(n)");            f[2].log2_value  = log2(50) + 0.5*log2n;
    strcpy(f[3].name,  "12*sqrt(n)");            f[3].log2_value  = log2(12) + 0.5*log2n;
    strcpy(f[4].name,  "n^0.51");                f[4].log2_value  = 0.51*log2n;
    strcpy(f[5].name,  "n*log2(n)");             f[5].log2_value  = log2n + log2(log2n);
    strcpy(f[6].name,  "100n^2 + 6n");           f[6].log2_value  = log2(100) + 2*log2n;
    strcpy(f[7].name,  "n^2 - 324");             f[7].log2_value  = 2*log2n;
    strcpy(f[8].name,  "2n^3");                  f[8].log2_value  = 1 + 3*log2n;
    strcpy(f[9].name,  "n^(log2 n)");            f[9].log2_value  = log2n * log2n;
    strcpy(f[10].name, "3^n");                   f[10].log2_value = n * log2(3.0);
    strcpy(f[11].name, "2^(32n)");               f[11].log2_value = 32.0 * n;

    qsort(f, 12, sizeof(Func), cmp);

    printf("Increasing order of growth (n = %.0f):\n", n);
    printf("---------------------------------------\n");
    for (int i = 0; i < 12; i++) {
        printf("%2d. %-16s  (log2 value ~ %.4f)\n", i + 1, f[i].name, f[i].log2_value);
    }
    return 0;
}

/*
 * Sample expected ordering (asymptotic, n -> large):
 *   1/n  <  log2(n)  <  50*sqrt(n) ~ 12*sqrt(n)  <  n^0.51
 *        <  n log2 n  <  100n^2+6n ~ n^2-324  <  2n^3
 *        <  n^(log2 n)  <  3^n  <  2^(32n)
 *
 * Note: 50*sqrt(n) and 12*sqrt(n) differ only by a constant factor,
 * so they are of the SAME growth order (Theta(sqrt n)); their relative
 * position can swap depending on n because of the constant, but neither
 * one asymptotically dominates the other. Same logic applies to
 * 100n^2+6n and n^2-324 (both Theta(n^2)).
 */