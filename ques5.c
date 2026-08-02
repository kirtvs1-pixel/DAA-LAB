/*
 * Q5: Find the Partition Point
 * ------------------------------
 * Problem: Array A[0..n-1] contains a run of 0's followed by a run of
 *          1's (e.g. 0 0 0 0 1 1 1). Find the index of the first 1
 *          (the exact transition point) efficiently.
 *
 * Naive approach : Linear scan, O(n).
 * Better approach: Binary search, exploiting the fact that the array
 *                  is "sorted" in the sense that all 0's precede all
 *                  1's. This is a classic binary-search-on-answer
 *                  problem.
 *
 * Algorithm (binary search):
 *   low = 0, high = n - 1
 *   result = n              // if array is all 0's, no transition
 *   while low <= high:
 *       mid = (low + high) / 2
 *       if A[mid] == 1:
 *           result = mid     // candidate transition point
 *           high = mid - 1   // look for an earlier 1
 *       else:
 *           low = mid + 1    // A[mid] == 0, search right half
 *   return result
 *
 * Time Complexity : O(log n)  -- binary search halves the range each step.
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int find_partition_point(int *A, int n) {
    int low = 0, high = n - 1;
    int result = n; /* default: no 1 found -> all zeros */

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (A[mid] == 1) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return result;
}

/* Builds a test array of n elements: 'zeros' zeros followed by 1's */
void build_array(int *A, int n, int zeros) {
    for (int i = 0; i < n; i++) {
        A[i] = (i < zeros) ? 0 : 1;
    }
}

int main(void) {
    int n = 20;
    int A[20];

    /* Example: 12 zeros followed by 8 ones */
    build_array(A, n, 12);

    printf("Array: ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");

    int idx = find_partition_point(A, n);
    if (idx == n) {
        printf("No transition found (array is all zeros).\n");
    } else {
        printf("Transition point (first index of 1): %d\n", idx);
    }

    /* Edge cases */
    int all_zeros[5] = {0, 0, 0, 0, 0};
    int all_ones[5]  = {1, 1, 1, 1, 1};
    printf("\nEdge case all-zeros -> index: %d (n = %d)\n", find_partition_point(all_zeros, 5), 5);
    printf("Edge case all-ones  -> index: %d\n", find_partition_point(all_ones, 5));

    return 0;
}