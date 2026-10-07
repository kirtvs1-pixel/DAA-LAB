#include <stdio.h>

long long nextTerm(long long n) {
    if (n % 2 == 0)
        return n / 2;
    return 3 * n + 1;
}

int countSteps(long long n) {
    int steps = 0;
    while (n != 1) {
        n = nextTerm(n);
        steps++;
    }
    return steps;
}

long long findPeak(long long n) {
    long long peak = n;
    while (n != 1) {
        n = nextTerm(n);
        if (n > peak)
            peak = n;
    }
    return peak;
}

void printTrajectory(long long n) {
    printf("%lld", n);
    while (n != 1) {
        n = nextTerm(n);
        printf(" -> %lld", n);
    }
    printf("\n");
}

void singleMode() {
    long long n;
    printf("Enter n: ");
    scanf("%lld", &n);
    if (n < 1) {
        printf("n must be positive\n");
        return;
    }
    printf("Trajectory: ");
    printTrajectory(n);
    printf("Steps: %d\n", countSteps(n));
    printf("Peak value: %lld\n", findPeak(n));
}

void intervalMode() {
    long long a, b, i;
    printf("Enter a and b: ");
    scanf("%lld %lld", &a, &b);
    if (a < 1 || b < a) {
        printf("Invalid interval\n");
        return;
    }

    int maxSteps = 0;
    long long maxStepsNum = a;
    long long maxPeak = 0, maxPeakNum = a;
    long long totalSteps = 0;

    for (i = a; i <= b; i++) {
        int steps = countSteps(i);
        long long peak = findPeak(i);
        totalSteps += steps;
        if (steps > maxSteps) {
            maxSteps = steps;
            maxStepsNum = i;
        }
        if (peak > maxPeak) {
            maxPeak = peak;
            maxPeakNum = i;
        }
    }

    printf("Longest trajectory: n = %lld (%d steps)\n", maxStepsNum, maxSteps);
    printf("Highest peak: n = %lld (peak %lld)\n", maxPeakNum, maxPeak);
    printf("Average steps: %.2f\n", (double)totalSteps / (b - a + 1));
}

int main() {
    int choice;
    printf("1. Single value\n2. Interval [a, b]\nChoice: ");
    scanf("%d", &choice);
    if (choice == 1)
        singleMode();
    else if (choice == 2)
        intervalMode();
    else
        printf("Invalid choice\n");
    return 0;
}