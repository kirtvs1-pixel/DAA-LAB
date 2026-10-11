
#include <stdio.h>

#define MAX 1000

int heap[MAX + 1];
int size = 0;

void insert(int value) {
    int i = ++size;

    while (i > 1 && heap[i / 2] > value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

int extractMin(void) {
    int result = heap[1];
    int last = heap[size--];
    int i = 1, child;

    while (i * 2 <= size) {
        child = i * 2;

        if (child + 1 <= size &&
            heap[child + 1] < heap[child]) {
            child++;
        }

        if (last <= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (size > 0)
        heap[i] = last;

    return result;
}

int main(void) {
    int n, length;
    long long totalCost = 0;

    printf("Enter number of sticks: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of sticks.\n");
        return 1;
    }

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &length) != 1 || length < 0) {
            printf("Invalid stick length.\n");
            return 1;
        }

        insert(length);
    }

    while (size > 1) {
        int x = extractMin();
        int y = extractMin();

        long long cost = (long long)x + y;
        totalCost += cost;

        if (cost > 2147483647LL) {
            printf("Stick length exceeds supported integer range.\n");
            return 1;
        }

        insert((int)cost);
    }

    printf("Minimum total connection cost = %lld\n", totalCost);

    return 0;
}
