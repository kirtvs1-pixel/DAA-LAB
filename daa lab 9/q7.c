
#include <stdio.h>

#define MAX 1000

long long heap[MAX + 1];
int size = 0;

void insert(long long value) {
    int i = ++size;

    while (i > 1 && heap[i / 2] < value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

long long extractMax(void) {
    long long result = heap[1];
    long long last = heap[size--];
    int i = 1, child;

    while (i * 2 <= size) {
        child = i * 2;

        if (child + 1 <= size &&
            heap[child + 1] > heap[child]) {
            child++;
        }

        if (last >= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (size > 0)
        heap[i] = last;

    return result;
}

long long peekMax(void) {
    return heap[1];
}

int main(void) {
    int n;
    long long a[MAX];
    long long currentMin = 0;
    long long minDeviation;

    printf("Enter number of elements: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter positive integers:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &a[i]) != 1 || a[i] <= 0 ||
            a[i] > 4611686018427387903LL) {
            printf("Invalid element.\n");
            return 1;
        }

        if (a[i] % 2 != 0)
            a[i] *= 2;

        if (i == 0 || a[i] < currentMin)
            currentMin = a[i];

        insert(a[i]);
    }

    minDeviation = peekMax() - currentMin;

    while (peekMax() % 2 == 0) {
        long long maximum = extractMax();
        long long reduced = maximum / 2;

        if (reduced < currentMin)
            currentMin = reduced;

        insert(reduced);

        long long deviation = peekMax() - currentMin;

        if (deviation < minDeviation)
            minDeviation = deviation;
    }

    printf("Minimum deviation = %lld\n", minDeviation);

    return 0;
}
