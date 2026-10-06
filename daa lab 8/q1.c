#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minCoins(int *coins, int n, int V) {
    int *dp = malloc((V + 1) * sizeof(int));
    dp[0] = 0;
    for (int i = 1; i <= V; i++) {
        dp[i] = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX && dp[i - coins[j]] + 1 < dp[i])
                dp[i] = dp[i - coins[j]] + 1;
        }
    }
    int res = dp[V] == INT_MAX ? -1 : dp[V];
    free(dp);
    return res;
}

int main() {
    int n, V;
    printf("Enter number of denominations: ");
    scanf("%d", &n);
    int *coins = malloc(n * sizeof(int));
    printf("Enter denominations: ");
    for (int i = 0; i < n; i++) scanf("%d", &coins[i]);
    printf("Enter target amount: ");
    scanf("%d", &V);
    printf("Minimum coins: %d\n", minCoins(coins, n, V));
    free(coins);
    return 0;
}