#include <stdio.h>
#include <math.h>

int main() {
    int a[100], n, i, j;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // (i) Maximum
    int max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];

    printf("\nMaximum = %d", max);


    // (ii) First and Second Largest
    int largest = a[0], second = -999999;

    for (i = 1; i < n; i++) {
        if (a[i] > largest) {
            second = largest;
            largest = a[i];
        }
        else if (a[i] > second && a[i] != largest) {
            second = a[i];
        }
    }

    printf("\nLargest = %d", largest);
    printf("\nSecond Largest = %d", second);


    // (iii) Mean
    float sum = 0;

    for (i = 0; i < n; i++)
        sum += a[i];

    printf("\nMean = %.2f", sum / n);


    // (iv) Median
    // Sort array
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    float median;

    if (n % 2 == 0)
        median = (a[n/2 - 1] + a[n/2]) / 2.0;
    else
        median = a[n/2];

    printf("\nMedian = %.2f", median);


    // (v) Standard Deviation
    float mean = sum / n;
    float variance = 0;

    for (i = 0; i < n; i++)
        variance += (a[i] - mean) * (a[i] - mean);

    variance = variance / n;

    printf("\nStandard Deviation = %.2f", sqrt(variance));


    // (vi) Mode
    int mode = a[0], maxCount = 0;

    for (i = 0; i < n; i++) {
        int count = 0;

        for (j = 0; j < n; j++) {
            if (a[i] == a[j])
                count++;
        }

        if (count > maxCount) {
            maxCount = count;
            mode = a[i];
        }
    }

    printf("\nMode = %d", mode);


    // (vii) Remove Duplicates
    int newSize = 0, duplicate;

    for (i = 0; i < n; i++) {
        duplicate = 0;

        for (j = 0; j < newSize; j++) {
            if (a[i] == a[j]) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            a[newSize] = a[i];
            newSize++;
        }
    }

    printf("\nArray after removing duplicates: ");
    for (i = 0; i < newSize; i++)
        printf("%d ", a[i]);


    // (viii) Reverse
    int start = 0, end = newSize - 1;

    while (start < end) {
        int temp = a[start];
        a[start] = a[end];
        a[end] = temp;

        start++;
        end--;
    }

    printf("\nReversed array: ");
    for (i = 0; i < newSize; i++)
        printf("%d ", a[i]);


    // (ix) Partition with pivot
    int pivot;
    printf("\nEnter pivot: ");
    scanf("%d", &pivot);

    start = 0;
    end = newSize - 1;

    while (start <= end) {

        while (start < newSize && a[start] < pivot)
            start++;

        while (end >= 0 && a[end] >= pivot)
            end--;

        if (start < end) {
            int temp = a[start];
            a[start] = a[end];
            a[end] = temp;

            start++;
            end--;
        }
    }

    printf("Array after partition: ");
    for (i = 0; i < newSize; i++)
        printf("%d ", a[i]);

    return 0;
}