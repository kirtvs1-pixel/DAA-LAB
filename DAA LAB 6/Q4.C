#include <stdio.h>

long long totalCost = 0;
long long reversalCount = 0;

void reverseRange(int p[], int i, int j)
{
    if (i >= j)
        return;

    int left = i;
    int right = j;

    while (left < right)
    {
        int temp = p[left];
        p[left] = p[right];
        p[right] = temp;

        left++;
        right--;
    }

    reversalCount++;
    totalCost += (j - i + 1);
}

/*
   Partitions p[l...r] into:

   values <= mid | values > mid
*/
void partitionRange(int p[], int l, int r, int mid)
{
    if (l >= r)
        return;

    int q = (l + r) / 2;

    /* Partition both halves */
    partitionRange(p, l, q, mid);
    partitionRange(p, q + 1, r, mid);

    /*
       After recursion:

       Left  = small | large
       Right = small | large

       We need:

       small | small | large | large
    */

    int i = l;

    /* First large element in left half */
    while (i <= q && p[i] <= mid)
        i++;

    int j = q + 1;

    /* First large element in right half */
    while (j <= r && p[j] <= mid)
        j++;

    /*
       Reverse:

       large(left) | small(right)

       This becomes:

       small(right) | large(left)
    */
    if (i < j)
        reverseRange(p, i, j - 1);
}


/*
   Sort p[l...r].

   Values present in this segment are
   exactly lo ... hi.
*/
void sortRange(int p[], int l, int r, int lo, int hi)
{
    if (l >= r || lo >= hi)
        return;

    int mid = (lo + hi) / 2;

    /* Partition according to value */
    partitionRange(p, l, r, mid);

    /*
       Number of values in left part:
       lo ... mid
    */
    int leftSize = mid - lo + 1;

    /* Sort left part */
    sortRange(p,
              l,
              l + leftSize - 1,
              lo,
              mid);

    /* Sort right part */
    sortRange(p,
              l + leftSize,
              r,
              mid + 1,
              hi);
}

void printArray(int p[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int p[n];

    printf("Enter permutation: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("\nOriginal permutation: ");
    printArray(p, n);

    sortRange(p, 0, n - 1, 1, n);

    printf("Sorted permutation:   ");
    printArray(p, n);

    printf("\nNumber of reversals = %lld\n", reversalCount);
    printf("Total reversal cost  = %lld\n", totalCost);

    return 0;
}