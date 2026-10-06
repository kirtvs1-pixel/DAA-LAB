#include <stdio.h>
#include <stdlib.h>

unsigned long long countWays(int *coins, int n, int V)
{
    unsigned long long *dp = calloc(V + 1, sizeof(unsigned long long));
    dp[0] = 1;
    for (int j = 0; j < n; j++)
    {
        for (int i = coins[j]; i <= V; i++)
        {
            dp[i] += dp[i - coins[j]];
        }
    }
    unsigned long long res = dp[V];
    free(dp);
    return res;
}

int main()
{
    int n, V;
    printf("Enter number of denominations: ");
    scanf("%d", &n);
    int *coins = malloc(n * sizeof(int));
    printf("Enter denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);
    printf("Enter target amount: ");
    scanf("%d", &V);
    printf("Number of combinations: %llu\n", countWays(coins, n, V));
    free(coins);
    return 0;
}