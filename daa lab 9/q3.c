
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int d;
    int f;
} Station;

int compare(const void *a, const void *b) {
    const Station *x = a;
    const Station *y = b;
    return (x->d > y->d) - (x->d < y->d);
}

void push(int heap[], int *size, int value) {
    int i = ++(*size);

    while (i > 1 && heap[i / 2] < value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

int pop(int heap[], int *size) {
    int result = heap[1];
    int last = heap[(*size)--];
    int i = 1, child;

    while (i * 2 <= *size) {
        child = i * 2;

        if (child + 1 <= *size &&
            heap[child + 1] > heap[child])
            child++;

        if (last >= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    heap[i] = last;
    return result;
}

int minStops(int D, int F, Station s[], int n) {
    qsort(s, n, sizeof(Station), compare);

    int heap[MAX + 1];
    int size = 0;
    int i = 0;
    long long reach = F;
    int stops = 0;

    while (reach < D) {
        while (i < n && s[i].d <= reach) {
            push(heap, &size, s[i].f);
            i++;
        }

        if (size == 0)
            return -1;

        reach += pop(heap, &size);
        stops++;
    }

    return stops;
}

int main(void) {
    int D, F, n;
    Station s[MAX];

    printf("Enter target distance and initial fuel: ");
    if (scanf("%d %d", &D, &F) != 2 ||
        D < 0 || F < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter number of stations: ");
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX) {
        printf("Invalid number of stations.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter distance and fuel for station %d: ", i + 1);

        if (scanf("%d %d", &s[i].d, &s[i].f) != 2 ||
            s[i].d < 0 || s[i].f < 0 || s[i].d > D) {
            printf("Invalid station data.\n");
            return 1;
        }
    }

    int ans = minStops(D, F, s, n);

    if (ans == -1)
        printf("Target cannot be reached.\n");
    else
        printf("Minimum refuelling stops = %d\n", ans);

    return 0;
}
