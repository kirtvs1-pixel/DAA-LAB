
#include <stdio.h>

#define MAX 1000

int main(void) {
    int n;
    int rating[MAX];
    int candies[MAX];
    long long total = 0;

    printf("Enter number of children: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of children.\n");
        return 1;
    }

    printf("Enter ratings of children:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &rating[i]) != 1) {
            printf("Invalid rating.\n");
            return 1;
        }

        candies[i] = 1;
    }

    /* Left-to-right pass */
    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    /* Right-to-left pass */
    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1]) {
            int required = candies[i + 1] + 1;

            if (candies[i] < required) {
                candies[i] = required;
            }
        }
    }

    /* Calculate total candies */
    for (int i = 0; i < n; i++) {
        total += candies[i];
    }

    printf("\nRating\tCandies\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", rating[i], candies[i]);
    }

    printf("\nMinimum total candies = %lld\n", total);

    return 0;
}
