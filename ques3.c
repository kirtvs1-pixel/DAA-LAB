/*
 * Q3: Performance Analysis of Bubble Sort
 * ----------------------------------------
 * Implements two variants of bubble sort on randomised data:
 *
 *   (i)  Adaptive bubble sort: stops early if no swaps occur in a
 *        pass (array already sorted before the (n-1)th pass).
 *   (ii) Non-adaptive bubble sort: always runs the full (n-1) passes
 *        regardless of whether the array becomes sorted earlier.
 *
 * Both versions count the number of COMPARISONS performed, for
 * randomly generated arrays of increasing size, so the counts can be
 * plotted (e.g. in Excel/Python/gnuplot) using the CSV this program
 * prints to stdout.
 *
 * Time Complexity:
 *   Adaptive bubble sort     : Best case O(n)      [already sorted]
 *                              Worst/Avg case O(n^2)
 *   Non-adaptive bubble sort : Always O(n^2) comparisons,
 *                              regardless of input order.
 * Space Complexity: O(1) auxiliary (in-place), O(n) for the array itself.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Fills array with random integers in [0, 10000) */
void fill_random(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;
}

void copy_array(int *dst, int *src, int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

/* Version (i): terminates early if sorted before pass n-1 */
long bubble_sort_adaptive(int *arr, int n) {
    long comparisons = 0;
    int swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
                swapped = 1;
            }
        }
        if (!swapped) break;  /* array already sorted -> stop early */
    }
    return comparisons;
}

/* Version (ii): always completes all (n-1) passes */
long bubble_sort_full(int *arr, int n) {
    long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
        }
    }
    return comparisons;
}

int main(void) {
    srand((unsigned) time(NULL));

    int sizes[] = {100, 200, 400, 800, 1600, 3200};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("n,comparisons_adaptive,comparisons_full\n");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *original = malloc(n * sizeof(int));
        int *a1 = malloc(n * sizeof(int));
        int *a2 = malloc(n * sizeof(int));

        fill_random(original, n);
        copy_array(a1, original, n);
        copy_array(a2, original, n);

        long c1 = bubble_sort_adaptive(a1, n);
        long c2 = bubble_sort_full(a2, n);

        printf("%d,%ld,%ld\n", n, c1, c2);

        free(original); free(a1); free(a2);
    }

    fprintf(stderr, "\nConclusion: For random data both versions perform\n");
    fprintf(stderr, "close to n(n-1)/2 comparisons since early termination\n");
    fprintf(stderr, "rarely triggers on random input. The adaptive version's\n");
    fprintf(stderr, "advantage (O(n) comparisons) only shows up clearly when\n");
    fprintf(stderr, "the input is already sorted or nearly sorted.\n");

    return 0;
}

/* To plot: redirect stdout to a CSV file, e.g.
 *   ./q3_bubble_sort > results.csv
 * then plot column 2 (adaptive) and column 3 (full) vs column 1 (n).
 */