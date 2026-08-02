/*
 * Q2: Fair vs Biased Coin
 * -----------------------
 * Goal : Simulate coin tosses in C to empirically show that a fair
 *        coin gives P(HEAD) ~ 0.5, then extend to a biased coin and
 *        compare.
 *
 * Algorithm (Monte Carlo simulation):
 *   1. For a fair coin, generate N random tosses; each toss is HEAD
 *      if a uniform random number in [0,1) < 0.5, else TAIL.
 *   2. For a biased coin, use a chosen bias p (e.g. 0.7) as the
 *      threshold instead of 0.5.
 *   3. Count heads, compute observed probability = heads / N.
 *   4. As N grows, observed probability converges to the true
 *      probability (Law of Large Numbers).
 *
 * Time Complexity : O(N) - one constant-time random draw per toss.
 * Space Complexity: O(1) - only counters are stored.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Returns 1 for HEAD, 0 for TAIL given bias p (probability of head) */
int toss(double p) {
    double r = (double) rand() / ((double) RAND_MAX + 1.0);
    return (r < p) ? 1 : 0;
}

double simulate(double p, long N) {
    long heads = 0;
    for (long i = 0; i < N; i++) {
        heads += toss(p);
    }
    return (double) heads / (double) N;
}

int main(void) {
    srand((unsigned) time(NULL));

    long trial_sizes[] = {100, 1000, 10000, 100000, 1000000};
    int num_trials = sizeof(trial_sizes) / sizeof(trial_sizes[0]);

    printf("---- FAIR COIN (p = 0.5) ----\n");
    printf("%-10s %-15s\n", "N", "P(HEAD) observed");
    for (int i = 0; i < num_trials; i++) {
        double observed = simulate(0.5, trial_sizes[i]);
        printf("%-10ld %-15.5f\n", trial_sizes[i], observed);
    }

    double biased_p = 0.7; /* biased coin: 70% chance of head */
    printf("\n---- BIASED COIN (true p = %.2f) ----\n", biased_p);
    printf("%-10s %-15s\n", "N", "P(HEAD) observed");
    for (int i = 0; i < num_trials; i++) {
        double observed = simulate(biased_p, trial_sizes[i]);
        printf("%-10ld %-15.5f\n", trial_sizes[i], observed);
    }

    printf("\nConclusion: As N increases, the observed probability for\n");
    printf("the fair coin converges to 0.5, and for the biased coin it\n");
    printf("converges to the chosen bias (%.2f), illustrating the Law\n", biased_p);
    printf("of Large Numbers.\n");

    return 0;
}