#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Merge two sorted arrays */
void merge(int a[], int n1, int b[], int n2, int result[])
{
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2)
    {
        if (a[i] < b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < n1)
        result[k++] = a[i++];

    while (j < n2)
        result[k++] = b[j++];
}


/* Method 1 */
void method1(int arr[][100], int k, int n, int result[])
{
    int size = n;

    for (int i = 0; i < n; i++)
        result[i] = arr[0][i];

    for (int i = 1; i < k; i++)
    {
        int *temp = malloc((size + n) * sizeof(int));

        merge(result, size, arr[i], n, temp);

        for (int j = 0; j < size + n; j++)
            result[j] = temp[j];

        size += n;

        free(temp);
    }
}


/* Method 2 */
void method2(int arr[][100], int k, int n, int result[])
{
    int total = k * n;

    int *current = malloc(total * sizeof(int));

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            current[i * n + j] = arr[i][j];
        }
    }

    int arrays = k;
    int size = n;

    while (arrays > 1)
    {
        int newArrays = 0;

        for (int i = 0; i < arrays; i += 2)
        {
            if (i + 1 < arrays)
            {
                int *temp = malloc(2 * size * sizeof(int));

                merge(
                    current + i * size,
                    size,
                    current + (i + 1) * size,
                    size,
                    temp
                );

                for (int j = 0; j < 2 * size; j++)
                    current[(newArrays * 2 * size) + j] = temp[j];

                free(temp);

                newArrays++;
            }
        }

        arrays = newArrays;
        size = size * 2;
    }

    for (int i = 0; i < total; i++)
        result[i] = current[i];

    free(current);
}


int main()
{
    FILE *fp;

    fp = fopen("growth.csv", "w");

    if (fp == NULL)
    {
        printf("File error!\n");
        return 1;
    }

    fprintf(fp, "k,Method1,Method2\n");

    printf("k\tMethod 1\tMethod 2\n");
    printf("-----------------------------\n");

    int n = 100;

    for (int k = 2; k <= 32; k *= 2)
    {
        int arr[32][100];

        /* Create sorted arrays */
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < n; j++)
            {
                arr[i][j] = i * n + j;
            }
        }

        int total = k * n;

        int *result1 = malloc(total * sizeof(int));
        int *result2 = malloc(total * sizeof(int));

        clock_t start, end;

        /* Method 1 */
        start = clock();

        method1(arr, k, n, result1);

        end = clock();

        double time1 =
            (double)(end - start) / CLOCKS_PER_SEC;


        /* Method 2 */
        start = clock();

        method2(arr, k, n, result2);

        end = clock();

        double time2 =
            (double)(end - start) / CLOCKS_PER_SEC;


        printf("%d\t%.6f\t%.6f\n",
               k, time1, time2);

        fprintf(fp, "%d,%.6f,%.6f\n",
                k, time1, time2);

        free(result1);
        free(result2);
    }

    fclose(fp);

    printf("-----------------------------\n");
    printf("Data saved in growth.csv\n");

    return 0;
}