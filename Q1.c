
#include <stdio.h>
#include <stdlib.h>

long long binaryComparisons = 0;
long long ternaryComparisons = 0;

/* Binary Search with comparison counting */
int binarySearch(int arr[], int n, int x) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        binaryComparisons++;
        if (arr[mid] == x)
            return mid;

        binaryComparisons++;
        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/* Ternary Search with comparison counting */
int ternarySearch(int arr[], int n, int x) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        ternaryComparisons++;
        if (arr[mid1] == x)
            return mid1;

        ternaryComparisons++;
        if (arr[mid2] == x)
            return mid2;

        ternaryComparisons++;
        if (x < arr[mid1])
            high = mid1 - 1;
        else {
            ternaryComparisons++;
            if (x > arr[mid2])
                low = mid2 + 1;
            else {
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }
    }

    return -1;
}

int main(void) {
    int n, x;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter sorted array: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &x);

    int b = binarySearch(arr, n, x);
    int t = ternarySearch(arr, n, x);

    printf("\nBinary Search index: %d\n", b);
    printf("Ternary Search index: %d\n", t);
    printf("Binary comparisons: %lld\n", binaryComparisons);
    printf("Ternary comparisons: %lld\n", ternaryComparisons);

    free(arr);
    return 0;
}

/*
For graph validation, compile this program and run it for different
values of n. Record the comparison counts.

A separate Python script, plot_search_comparisons.py, can generate
a graph from the recorded data.

Expected result:
Binary Search generally uses fewer comparisons than Ternary Search
because Binary Search makes fewer comparisons per iteration.
*/