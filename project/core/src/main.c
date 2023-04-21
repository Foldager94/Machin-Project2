#include <stdio.h>
#include "board.h"
#include "card.h"
int main() {
    Card *c;
    c = &(Card){.isFlipped = true, .cardValue = "T", .cardSuit = 'h'};
    printf("Card: %s%c (isFlipped = %d)\n", c->cardValue, c->cardSuit, c->isFlipped);
    return 0;
}


void printBoard() {
    printf("C1 \t C2 \t C3 \t C4 \t C5 \t C6 \t C7 \t \t ");
}
