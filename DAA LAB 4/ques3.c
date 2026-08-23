#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int binarySearch(int arr[], int n, int target, int start) {
    int low = start, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return 1;

        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

int findKSum(int arr[], int n, int k, int target, int start) {

    if (k == 2) {
        for (int i = start; i < n - 1; i++) {
            int needed = target - arr[i];

            if (binarySearch(arr, n, needed, i + 1))
                return 1;
        }

        return 0;
    }

    for (int i = start; i <= n - k; i++) {

        if (findKSum(arr, n, k - 1,
                     target - arr[i], i + 1))
            return 1;
    }

    return 0;
}

int main() {
    int n, k, T;

    printf("Enter n: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter T: ");
    scanf("%d", &T);

    qsort(arr, n, sizeof(int), compare);

    if (findKSum(arr, n, k, T, 0))
        printf("YES: %d elements can form %d\n", k, T);
    else
        printf("NO: No such combination exists.\n");

    return 0;
}