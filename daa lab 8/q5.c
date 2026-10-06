#include <stdio.h>
#include <stdlib.h>

long long msis(int *a, int n) {
    long long *dp = malloc(n * sizeof(long long));
    long long best = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = a[i];
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + a[i] > dp[i]) dp[i] = dp[j] + a[i];
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
    printf("Enter array of positive integers: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Maximum sum increasing subsequence: %lld\n", msis(a, n));
    free(a);
    return 0;
}