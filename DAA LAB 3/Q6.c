#include <stdio.h>

/*
 * Selection Sort
 *
 * Loop invariant:
 * At the start of every iteration i,
 * A[0...i-1] contains the i smallest elements
 * of the original array in sorted order.
 */

void selectionSort(int A[], int n) {

    for (int i = 0; i < n - 1; i++) {

        int minIndex = i;

        /* Find minimum in A[i...n-1] */
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[minIndex])
                minIndex = j;
        }

        /* Put minimum at position i */
        int temp = A[i];
        A[i] = A[minIndex];
        A[minIndex] = temp;
    }
}

int main(void) {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n];

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    selectionSort(A, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");

    return 0;
}

/*
Correctness using Loop Invariant:

Initialization:
Before the first iteration, the sorted prefix is empty,
so the invariant is true.

Maintenance:
The smallest element in the unsorted part is found and
placed at A[i]. Therefore the sorted prefix grows by one.

Termination:
After n-1 iterations, the first n-1 elements are sorted.
The last remaining element must be the largest, so the
whole array is sorted.

Time Complexity:
Best Case  = Theta(n^2)
Worst Case = Theta(n^2)

The best case is not faster because the algorithm still
scans the remaining unsorted elements on every iteration.

Space Complexity:
Theta(1) auxiliary space.
*/