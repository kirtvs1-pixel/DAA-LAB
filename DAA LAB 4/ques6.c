#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int point;
    int type;
} Event;

int compare(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    // Start (+1) before end (-1)
    return e2->type - e1->type;
}

int main() {
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event events[2 * n];

    for (int i = 0; i < n; i++) {
        int l, r;

        printf("Enter interval %d: ", i + 1);
        scanf("%d %d", &l, &r);

        events[2 * i].point = l;
        events[2 * i].type = 1;

        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int bestPoint = 0;

    for (int i = 0; i < 2 * n; i++) {

        current += events[i].type;

        if (current > maximum) {
            maximum = current;
            bestPoint = events[i].point;
        }
    }

    printf("\nPoint = %d\n", bestPoint);
    printf("Maximum overlapping intervals = %d\n", maximum);

    return 0;
}