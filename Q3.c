#include <stdio.h>

struct Pair {
    int max;
    int min;
};

struct Pair findMaxMin(int arr[], int low, int high) {
    struct Pair result, left, right;

    /* One element */
    if (low == high) {
        result.max = arr[low];
        result.min = arr[low];
        return result;
    }

    /* Two elements: only one comparison */
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }

    /* Divide */
    int mid = low + (high - low) / 2;

    /* Conquer */
    left = findMaxMin(arr, low, mid);
    right = findMaxMin(arr, mid + 1, high);

    /* Combine */
    result.max = (left.max > right.max) ? left.max : right.max;
    result.min = (left.min < right.min) ? left.min : right.min;

    return result;
}

int main(void) {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct Pair result = findMaxMin(arr, 0, n - 1);

    printf("Maximum = %d\n", result.max);
    printf("Minimum = %d\n", result.min);

    return 0;
}

/*
Time Complexity:
T(n) = 2T(n/2) + 2 = O(n)

For n being a power of 2:
Number of comparisons = 3n/2 - 2

Space Complexity:
O(log n) recursion stack.
*/