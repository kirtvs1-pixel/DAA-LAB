/*
 * Q4: Towers of Hanoi (ToH)
 * --------------------------
 * Algorithm (recursive):
 *   ToH(n, source, aux, dest):
 *     if n == 0: return
 *     ToH(n-1, source, dest, aux)      // move top n-1 discs out of the way
 *     move disc n from source to dest  // move the largest disc
 *     ToH(n-1, aux, source, dest)      // move n-1 discs onto dest
 *
 * Recurrence for number of moves:
 *   T(n) = 2*T(n-1) + 1,  T(0) = 0
 *   Solving -> T(n) = 2^n - 1
 *
 * Time Complexity : O(2^n)  -- exponential, since each call spawns two
 *                              recursive calls of size n-1.
 * Space Complexity: O(n)    -- recursion stack depth.
 */

#include <stdio.h>

long move_count = 0;

void toh(int n, char source, char aux, char dest, int print_moves) {
    if (n == 0) return;
    toh(n - 1, source, dest, aux, print_moves);
    move_count++;
    if (print_moves) {
        printf("Move disc %d from %c -> %c\n", n, source, dest);
    }
    toh(n - 1, aux, source, dest, print_moves);
}

int main(void) {
    printf("n,total_moves,formula_2^n_minus_1\n");
    for (int n = 1; n <= 20; n++) {
        move_count = 0;
        toh(n, 'A', 'B', 'C', 0);  /* set to 1 to print every move */
        long formula = (1L << n) - 1;
        printf("%d,%ld,%ld\n", n, move_count, formula);
    }

    printf("\nConclusion: The measured move count matches 2^n - 1 exactly,\n");
    printf("confirming the recurrence T(n) = 2T(n-1) + 1. Since moves grow\n");
    printf("exponentially, plotting n vs total_moves on a normal scale shows\n");
    printf("a sharply rising curve; plotting on a log scale (log2 of moves)\n");
    printf("gives a straight line, confirming O(2^n) growth.\n");

    return 0;
}