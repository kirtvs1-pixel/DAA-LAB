
#include <stdio.h>
#include <string.h>

#define MAX 1000
#define CHARS 52

typedef struct {
    int id;
    int freq;
} Item;

typedef struct {
    int id;
    int remaining;
    int releaseTime;
} Cooldown;

int getId(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 'a';

    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 26;

    return -1;
}

char getChar(int id) {
    if (id < 26)
        return 'a' + id;

    return 'A' + (id - 26);
}

void push(Item heap[], int *size, Item value) {
    int i = ++(*size);

    while (i > 1 && heap[i / 2].freq < value.freq) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

Item pop(Item heap[], int *size) {
    Item result = heap[1];
    Item last = heap[(*size)--];
    int i = 1, child;

    while (i * 2 <= *size) {
        child = i * 2;

        if (child + 1 <= *size &&
            heap[child + 1].freq > heap[child].freq) {
            child++;
        }

        if (last.freq >= heap[child].freq)
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (*size > 0)
        heap[i] = last;

    return result;
}

int main(void) {
    char s[MAX + 1], result[MAX + 1];
    int freq[CHARS] = {0};
    Item heap[CHARS + 1];
    Cooldown queue[CHARS + 1];

    int heapSize = 0;
    int front = 0, rear = 0;
    int n, k, time = 0, out = 0;

    printf("Enter string (letters only): ");
    if (scanf("%1000s", s) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    n = (int)strlen(s);

    printf("Enter K: ");
    if (scanf("%d", &k) != 1 || k < 0) {
        printf("Invalid K.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int id = getId(s[i]);

        if (id == -1) {
            printf("Only English letters are supported.\n");
            return 1;
        }

        freq[id]++;
    }

    if (k <= 1) {
        printf("Reorganised string: %s\n", s);
        return 0;
    }

    for (int i = 0; i < CHARS; i++) {
        if (freq[i] > 0) {
            Item item = {i, freq[i]};
            push(heap, &heapSize, item);
        }
    }

    while (out < n) {
        /* Release characters whose cooldown has ended */
        if (front < rear &&
            queue[front].releaseTime <= time) {
            Item item = {queue[front].id,
                         queue[front].remaining};

            push(heap, &heapSize, item);
            front++;
        }

        if (heapSize == 0) {
            printf("Reorganisation is impossible.\n");
            return 0;
        }

        Item current = pop(heap, &heapSize);

        result[out++] = getChar(current.id);
        current.freq--;

        if (current.freq > 0) {
            Cooldown item = {
                current.id,
                current.freq,
                time + k
            };

            queue[rear++] = item;
        }

        time++;
    }

    result[out] = '\0';

    printf("Reorganised string: %s\n", result);

    return 0;
}
