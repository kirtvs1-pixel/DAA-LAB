
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    char symbol;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct {
    char symbol;
    int freq;
    int length;
    char code[MAX];
} Symbol;

Node *createNode(char symbol, int freq) {
    Node *node = malloc(sizeof(Node));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    node->symbol = symbol;
    node->freq = freq;
    node->left = node->right = NULL;

    return node;
}

void findLengths(Node *root, int depth,
                 Symbol symbols[], int n) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        for (int i = 0; i < n; i++) {
            if (symbols[i].symbol == root->symbol) {
                symbols[i].length = (depth == 0) ? 1 : depth;
                break;
            }
        }
        return;
    }

    findLengths(root->left, depth + 1, symbols, n);
    findLengths(root->right, depth + 1, symbols, n);
}

Node *buildHuffman(Symbol symbols[], int n) {
    Node *nodes[2 * MAX];
    int count = n;

    for (int i = 0; i < n; i++)
        nodes[i] = createNode(symbols[i].symbol,
                              symbols[i].freq);

    while (count > 1) {
        int first = -1, second = -1;

        for (int i = 0; i < count; i++) {
            if (first == -1 ||
                nodes[i]->freq < nodes[first]->freq) {
                second = first;
                first = i;
            } else if (second == -1 ||
                       nodes[i]->freq < nodes[second]->freq) {
                second = i;
            }
        }

        Node *parent = createNode(
            '#', nodes[first]->freq + nodes[second]->freq
        );

        parent->left = nodes[first];
        parent->right = nodes[second];

        if (first > second) {
            int temp = first;
            first = second;
            second = temp;
        }

        nodes[first] = parent;
        nodes[second] = nodes[count - 1];
        count--;
    }

    return nodes[0];
}

int compareSymbols(const void *a, const void *b) {
    const Symbol *x = a;
    const Symbol *y = b;

    if (x->length != y->length)
        return x->length - y->length;

    return (unsigned char)x->symbol -
           (unsigned char)y->symbol;
}

void generateCanonicalCodes(Symbol symbols[], int n) {
    qsort(symbols, n, sizeof(Symbol), compareSymbols);

    char code[MAX] = "0";

    for (int i = 0; i < symbols[0].length; i++)
        code[i] = '0';

    code[symbols[0].length] = '\0';
    strcpy(symbols[0].code, code);

    for (int i = 1; i < n; i++) {
        int j = (int)strlen(code) - 1;

        while (j >= 0 && code[j] == '1') {
            code[j] = '0';
            j--;
        }

        if (j >= 0)
            code[j] = '1';

        int len = (int)strlen(code);

        while (len < symbols[i].length)
            code[len++] = '0';

        code[len] = '\0';
        strcpy(symbols[i].code, code);
    }
}

int main(void) {
    int n;
    Symbol symbols[MAX];

    printf("Enter number of symbols (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter symbol and positive frequency: ");

        if (scanf(" %c %d", &symbols[i].symbol,
                  &symbols[i].freq) != 2 ||
            symbols[i].freq <= 0) {
            printf("Invalid input.\n");
            return 1;
        }

        for (int j = 0; j < i; j++) {
            if (symbols[j].symbol == symbols[i].symbol) {
                printf("Duplicate symbol is not allowed.\n");
                return 1;
            }
        }
    }

    Node *root = buildHuffman(symbols, n);

    findLengths(root, 0, symbols, n);
    generateCanonicalCodes(symbols, n);

    double totalFrequency = 0;
    double weightedLength = 0;

    printf("\nCanonical Huffman Codebook\n");
    printf("--------------------------------\n");
    printf("Symbol\tFrequency\tLength\tCode\n");

    for (int i = 0; i < n; i++) {
        printf("%c\t%d\t\t%d\t%s\n",
               symbols[i].symbol,
               symbols[i].freq,
               symbols[i].length,
               symbols[i].code);

        totalFrequency += symbols[i].freq;
        weightedLength +=
            symbols[i].freq * symbols[i].length;
    }

    printf("--------------------------------\n");
    printf("Expected code length: %.3f\n",
           weightedLength / totalFrequency);

    return 0;
}
