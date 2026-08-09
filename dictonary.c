#include <stdio.h>
#include <math.h>

int main()
{
    FILE *fp;

    fp = fopen("growth.csv", "w");

    if (fp == NULL)
    {
        printf("File could not be created!\n");
        return 1;
    }

    fprintf(fp,
        "n,UnsortedArray,SortedArray,SLLUnsorted,SLLSorted,DLLUnsorted,DLLSorted\n");

    printf("n\tUnsorted\tSorted\tSLL-Unsorted\tSLL-Sorted\tDLL-Unsorted\tDLL-Sorted\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int n = 10; n <= 1000; n += 10)
    {
        /*
            Search:
            Unsorted Array       -> O(n)
            Sorted Array         -> O(log n)
            SLL                  -> O(n)
            DLL                  -> O(n)
        */

        double unsorted = n;
        double sorted = log2(n);
        double sllUnsorted = n;
        double sllSorted = n;
        double dllUnsorted = n;
        double dllSorted = n;

        fprintf(fp,
            "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
            n,
            unsorted,
            sorted,
            sllUnsorted,
            sllSorted,
            dllUnsorted,
            dllSorted
        );

        /* Display only some values */
        if (n % 100 == 0)
        {
            printf("%d\t%.2f\t\t%.2f\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",
                n,
                unsorted,
                sorted,
                sllUnsorted,
                sllSorted,
                dllUnsorted,
                dllSorted
            );
        }
    }

    fclose(fp);

    printf("\nData saved successfully in growth.csv\n");

    return 0;
}