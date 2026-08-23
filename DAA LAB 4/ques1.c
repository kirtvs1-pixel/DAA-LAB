#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    char colour;
} Item;

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item *red = malloc(n * sizeof(Item));
    Item *blue = malloc(n * sizeof(Item));
    Item *yellow = malloc(n * sizeof(Item));

    int r = 0, b = 0, y = 0;

    printf("Enter number and colour (R/B/Y):\n");

    for (int i = 0; i < n; i++) {
        int num;
        char c;

        scanf("%d %c", &num, &c);

        if (c == 'R')
            red[r++] = (Item){num, c};
        else if (c == 'B')
            blue[b++] = (Item){num, c};
        else if (c == 'Y')
            yellow[y++] = (Item){num, c};
    }

    printf("\nSorted by colour:\n");

    for (int i = 0; i < r; i++)
        printf("(%d, R) ", red[i].number);

    for (int i = 0; i < b; i++)
        printf("(%d, B) ", blue[i].number);

    for (int i = 0; i < y; i++)
        printf("(%d, Y) ", yellow[i].number);

    free(red);
    free(blue);
    free(yellow);

    return 0;
}