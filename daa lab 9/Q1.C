
#include <stdio.h>

typedef struct {
    int id;
    double value;
    double weight;
    double decay;
    double fraction;
} Item;

int main() {
    int n;
    double W, totalValue = 0.0;
    double time = 0.0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item a[n];

    for (int i = 0; i < n; i++) {
        a[i].id = i + 1;
        printf("Enter value, weight and decay rate for item %d: ",
               i + 1);
        scanf("%lf %lf %lf",
              &a[i].value, &a[i].weight, &a[i].decay);

        a[i].fraction = 0.0;
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    while (W > 1e-9) {
        int best = -1;
        double bestDensity = 0.0;

        for (int i = 0; i < n; i++) {
            if (a[i].fraction >= 1.0 - 1e-9)
                continue;

            double density =
                a[i].value / a[i].weight
                - a[i].decay * time;

            if (density > bestDensity) {
                bestDensity = density;
                best = i;
            }
        }

        if (best == -1)
            break;

        double available =
            a[best].weight * (1.0 - a[best].fraction);

        double take = (W < available) ? W : available;

        double fraction = take / a[best].weight;

        a[best].fraction += fraction;
        totalValue += take * bestDensity;
        W -= take;

        printf("Time %.2f: Item %d, fraction taken = %.2f\n",
               time, a[best].id, fraction);

        time += 1.0;

        if (take <= 1e-9)
            break;
    }

    printf("\nSelected fractions:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: %.2f\n",
               a[i].id, a[i].fraction);
    }

    printf("Total effective value = %.2f\n", totalValue);

    return 0;
}
