
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int parent[MAX];
int rankArr[MAX];

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unite(int u, int v)
{
    int rootU = find(u);
    int rootV = find(v);

    if (rootU == rootV)
        return;

    if (rankArr[rootU] < rankArr[rootV])
        parent[rootU] = rootV;
    else if (rankArr[rootU] > rankArr[rootV])
        parent[rootV] = rootU;
    else
    {
        parent[rootV] = rootU;
        rankArr[rootU]++;
    }
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, m;
    int A[MAX], result[MAX];
    int u, v, i, j;
    int count;

    int *values[MAX];
    int sizes[MAX] = {0};

    printf("Enter n and m: ");
    scanf("%d %d", &n, &m);

    if (n <= 0 || n > MAX || m < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter permutation:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);

        if (A[i] < 1 || A[i] > n)
        {
            printf("Invalid permutation.\n");
            return 1;
        }

        parent[i] = i;
        rankArr[i] = 0;
        result[i] = A[i];
    }

    printf("Enter swap edges (1-based indices):\n");

    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);

        if (u < 1 || u > n || v < 1 || v > n)
        {
            printf("Invalid edge.\n");
            return 1;
        }

        unite(u - 1, v - 1);
    }

    /* Count values in each component */
    for (i = 0; i < n; i++)
        sizes[find(i)]++;

    /* Allocate storage for each component */
    for (i = 0; i < n; i++)
    {
        if (sizes[i] > 0)
        {
            values[i] = malloc(sizes[i] * sizeof(int));

            if (values[i] == NULL)
            {
                printf("Memory allocation failed.\n");
                return 1;
            }

            sizes[i] = 0;
        }
    }

    /* Collect values by component */
    for (i = 0; i < n; i++)
    {
        int root = find(i);
        values[root][sizes[root]++] = A[i];
    }

    /* Sort values in every component */
    for (i = 0; i < n; i++)
    {
        if (sizes[i] > 0)
            qsort(values[i], sizes[i], sizeof(int), compare);

        sizes[i] = 0;
    }

    /* Assign sorted values to indices in increasing order */
    for (i = 0; i < n; i++)
    {
        int root = find(i);
        result[i] = values[root][sizes[root]++];
    }

    printf("Lexicographically smallest permutation:\n");

    for (i = 0; i < n; i++)
        printf("%d ", result[i]);

    printf("\n");

    for (i = 0; i < n; i++)
    {
        if (values[i] != NULL)
            free(values[i]);
    }

    return 0;
}
