
#include <stdio.h>

#define MAX 100

int main(void) {
    int n;
    long long w[MAX];
    int external[MAX];
    long long totalCost = 0;

    printf("Enter number of weights: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of weights.\n");
        return 1;
    }

    printf("Enter weights in their given order:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &w[i]) != 1 || w[i] < 0) {
            printf("Invalid weight.\n");
            return 1;
        }

        external[i] = 1;
    }

    int count = n;
    int step = 1;

    while (count > 1) {
        int bestI = -1, bestJ = -1;
        long long bestSum = 0;

        /* Find the minimum compatible pair */
        for (int i = 0; i < count; i++) {
            for (int j = i + 1; j < count; j++) {
                int compatible = 1;

                /* No external node may lie between i and j */
                for (int k = i + 1; k < j; k++) {
                    if (external[k]) {
                        compatible = 0;
                        break;
                    }
                }

                if (compatible) {
                    if (w[i] > 9223372036854775807LL - w[j]) {
                        printf("Weight sum overflow.\n");
                        return 1;
                    }

                    long long sum = w[i] + w[j];

                    if (bestI == -1 || sum < bestSum) {
                        bestI = i;
                        bestJ = j;
                        bestSum = sum;
                    }
                }
            }
        }

        if (bestI == -1) {
            printf("No compatible pair found.\n");
            return 1;
        }

        printf("Step %d: Merge %lld and %lld -> %lld\n",
               step++, w[bestI], w[bestJ], bestSum);

        totalCost += bestSum;

        /* Replace left node with merged internal node */
        w[bestI] = bestSum;
        external[bestI] = 0;

        /* Remove right node */
        for (int i = bestJ; i < count - 1; i++) {
            w[i] = w[i + 1];
            external[i] = external[i + 1];
        }

        count--;
    }

    printf("Minimum weighted path length = %lld\n", totalCost);

    return 0;
}
