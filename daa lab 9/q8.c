
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int start;
    int end;
} Meeting;

int heap[MAX + 1];
int heapSize = 0;

int compareMeetings(const void *a, const void *b) {
    const Meeting *x = a;
    const Meeting *y = b;

    if (x->start < y->start) return -1;
    if (x->start > y->start) return 1;
    return 0;
}

void insert(int endTime) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] > endTime) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = endTime;
}

int extractMin(void) {
    int result = heap[1];
    int last = heap[heapSize--];
    int i = 1, child;

    while (i * 2 <= heapSize) {
        child = i * 2;

        if (child + 1 <= heapSize &&
            heap[child + 1] < heap[child]) {
            child++;
        }

        if (last <= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return result;
}

int minMeetingRooms(Meeting meetings[], int n) {
    qsort(meetings, n, sizeof(Meeting), compareMeetings);

    int maxRooms = 0;

    for (int i = 0; i < n; i++) {
        /* Reuse rooms whose meetings have ended */
        while (heapSize > 0 &&
               heap[1] <= meetings[i].start) {
            extractMin();
        }

        insert(meetings[i].end);

        if (heapSize > maxRooms)
            maxRooms = heapSize;
    }

    return maxRooms;
}

int main(void) {
    int n;
    Meeting meetings[MAX];

    printf("Enter number of meetings: ");

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX) {
        printf("Invalid number of meetings.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter start and end time of meeting %d: ", i + 1);

        if (scanf("%d %d", &meetings[i].start,
                  &meetings[i].end) != 2 ||
            meetings[i].start >= meetings[i].end) {
            printf("Invalid meeting interval.\n");
            return 1;
        }
    }

    if (n == 0) {
        printf("Minimum meeting rooms required = 0\n");
        return 0;
    }

    printf("Minimum meeting rooms required = %d\n",
           minMeetingRooms(meetings, n));

    return 0;
}

