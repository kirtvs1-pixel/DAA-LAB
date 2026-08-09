#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Normal Merge Sort */
void mergeSort(int a[], int n)
{
    if (n <= 1)
        return;

    int mid = n / 2;

    mergeSort(a, mid);
    mergeSort(a + mid, n - mid);

    int *temp = malloc(n * sizeof(int));

    int i = 0, j = mid, k = 0;

    while (i < mid && j < n)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i < mid)
        temp[k++] = a[i++];

    while (j < n)
        temp[k++] = a[j++];

    for (i = 0; i < n; i++)
        a[i] = temp[i];

    free(temp);
}


/* Modified 3-Way Merge Sort */
void threeWayMergeSort(int a[], int n)
{
    if (n <= 2)
        return;

    int x = n / 3;
    int y = n / 3;
    int z = n - x - y;

    threeWayMergeSort(a, x);
    threeWayMergeSort(a + x, y);
    threeWayMergeSort(a + x + y, z);

    int *temp = malloc(n * sizeof(int));

    int i = 0;
    int j = x;
    int k = x + y;
    int p = 0;

    while (i < x || j < x + y || k < n)
    {
        int smallest = 2147483647;

        if (i < x && a[i] < smallest)
            smallest = a[i];

        if (j < x + y && a[j] < smallest)
            smallest = a[j];

        if (k < n && a[k] < smallest)
            smallest = a[k];

        temp[p++] = smallest;

        if (i < x && a[i] == smallest)
            i++;
        else if (j < x + y && a[j] == smallest)
            j++;
        else
            k++;
    }

    for (i = 0; i < n; i++)
        a[i] = temp[i];

    free(temp);
}


int main()
{
    FILE *fp = fopen("growth.csv", "w");

    if (fp == NULL)
    {
        printf("Error creating file!\n");
        return 1;
    }

    fprintf(fp, "n,MergeSort,ThreeWayMergeSort\n");

    printf("n\tMerge Sort\t3-Way Merge Sort\n");
    printf("----------------------------------------\n");

    srand(time(NULL));

    for (int n = 100; n <= 2000; n += 100)
    {
        int *a = malloc(n * sizeof(int));
        int *b = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
        {
            a[i] = rand();
            b[i] = a[i];
        }

        clock_t start = clock();
        mergeSort(a, n);
        clock_t end = clock();

        double time1 =
            (double)(end - start) / CLOCKS_PER_SEC;


        start = clock();
        threeWayMergeSort(b, n);
        end = clock();

        double time2 =
            (double)(end - start) / CLOCKS_PER_SEC;


        printf("%d\t%.6f\t%.6f\n",
               n, time1, time2);

        fprintf(fp, "%d,%.6f,%.6f\n",
                n, time1, time2);

        free(a);
        free(b);
    }

    fclose(fp);

    printf("----------------------------------------\n");
    printf("Data saved in growth.csv\n");

    return 0;
}