#include <stdio.h>

/*
 * This program models a balance weighing operation.
 *
 * Assumptions:
 * 1. All normal coins have the same weight.
 * 2. There is at most one defective coin.
 * 3. If a defective coin exists, it is lighter.
 *
 * In the physical problem, one balance weighing is O(1).
 * The program represents the weighing by comparing group weights.
 */

int weigh(int coins[], int l1, int r1, int l2, int r2) {
    int sum1 = 0, sum2 = 0;

    for (int i = l1; i <= r1; i++)
        sum1 += coins[i];

    for (int i = l2; i <= r2; i++)
        sum2 += coins[i];

    if (sum1 < sum2)
        return -1;   // left group is lighter
    if (sum1 > sum2)
        return 1;    // right group is lighter

    return 0;        // equal
}

/*
 * Returns:
 *   index of defective coin, or
 *   -1 if no defective coin exists.
 */
int findDefective(int coins[], int low, int high) {
    int n = high - low + 1;

    if (n == 1)
        return -1;   // no reference coin is available here

    if (n == 2) {
        int result = weigh(coins, low, low, high, high);

        if (result < 0)
            return low;
        if (result > 0)
            return high;

        return -1;
    }

    int half = n / 2;

    int leftLow = low;
    int leftHigh = low + half - 1;

    int rightLow = leftHigh + 1;
    int rightHigh = rightLow + half - 1;

    int result = weigh(coins,
                       leftLow, leftHigh,
                       rightLow, rightHigh);

    if (result < 0)
        return findDefective(coins, leftLow, leftHigh);

    if (result > 0)
        return findDefective(coins, rightLow, rightHigh);

    /*
     * The two equal-sized groups balance.
     * If n is odd, one coin remains outside the two groups.
     */
    if (n % 2 == 1) {
        int leftover = rightHigh + 1;

        /*
         * Compare leftover with a known-good coin.
         * 'low' belongs to a group that balanced against
         * another equal group, so it is known to be good.
         */
        int result2 = weigh(coins,
                            leftover, leftover,
                            low, low);

        if (result2 < 0)
            return leftover;
    }

    return -1;
}

int main(void) {
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter coin weights:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    int index = findDefective(coins, 0, n - 1);

    if (index == -1)
        printf("None is defective.\n");
    else
        printf("Defective coin is at index: %d\n", index);

    return 0;
}