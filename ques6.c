/*
 * Q6: Element Uniqueness
 * ------------------------
 * Problem: Given n random numbers, check if any duplicates exist.
 *
 * Method 1 - Brute Force:
 *   Compare every pair (i, j), i < j. If any pair is equal, duplicate
 *   found.
 *   Time Complexity : O(n^2)
 *   Space Complexity: O(1) extra
 *
 * Method 2 - Sort then scan:
 *   Sort the array, then check adjacent elements for equality.
 *   Time Complexity : O(n log n)  (dominated by sorting)
 *   Space Complexity: O(1) extra if sorted in place (O(n) for the copy
 *                     kept here so the original array is untouched)
 *
 * Conclusion (for large n): The sort-based method scales far better.
 * E.g. for n = 20,000 the brute-force method performs ~2*10^8
 * comparisons while sort+scan performs on the order of n*log2(n)
 * (~20,000 * 14.3 ~ 2.9*10^5) element comparisons -- several orders
 * of magnitude fewer operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* Method 1: Brute force, O(n^2) */
int has_duplicate_bruteforce(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) return 1;
        }
    }
    return 0;
}

/* Method 2: Sort + adjacent scan, O(n log n) */
int has_duplicate_sorting(int *arr, int n) {
    int *copy = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) copy[i] = arr[i];

    qsort(copy, n, sizeof(int), cmp_int);

    int found = 0;
    for (int i = 0; i < n - 1; i++) {
        if (copy[i] == copy[i + 1]) { found = 1; break; }
    }
    free(copy);
    return found;
}

void fill_unique_random(int *arr, int n, int range) {
    /* Fill with random numbers; range should be >> n to keep duplicates rare
       unless we intentionally inject one for testing. */
    for (int i = 0; i < n; i++) arr[i] = rand() % range;
}

int main(void) {
    srand((unsigned) time(NULL));

    int sizes[] = {1000, 2000, 4000, 8000, 16000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("n,time_bruteforce_sec,time_sorting_sec\n");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *arr = malloc(n * sizeof(int));
        fill_unique_random(arr, n, n * 100); /* large range -> duplicates unlikely */

        clock_t t0 = clock();
        has_duplicate_bruteforce(arr, n);
        clock_t t1 = clock();
        has_duplicate_sorting(arr, n);
        clock_t t2 = clock();

        double time_bf = (double)(t1 - t0) / CLOCKS_PER_SEC;
        double time_srt = (double)(t2 - t1) / CLOCKS_PER_SEC;

        printf("%d,%.6f,%.6f\n", n, time_bf, time_srt);

        free(arr);
    }

    fprintf(stderr, "\nConclusion: As n grows, brute force time grows\n");
    fprintf(stderr, "quadratically while sort-based time grows near-linearly\n");
    fprintf(stderr, "(n log n), making sorting the clearly better approach\n");
    fprintf(stderr, "for large n.\n");

    return 0;
}