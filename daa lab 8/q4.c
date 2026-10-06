#include <stdio.h>
#include <stdlib.h>

int lis(int *a, int n) {
    int *dp = malloc(n * sizeof(int));
    int best = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
        }
        if (dp[i] > best) best = dp[i];
    }
    free(dp);
    return best;
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    printf("Enter array: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Length of LIS: %d\n", lis(a, n));
    free(a);
    return 0;
}