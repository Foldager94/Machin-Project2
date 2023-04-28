#include <stddef.h>
#include "card.h";
#include "board.h"

void insertNext(Card* dummy, Card* new) {
    if (dummy->previous->cardValue == ' ') {
        dummy->next = new;
        dummy->previous = new;
        new->next = dummy;
        new->previous = dummy;
    } else {
        Card* prevPtr = dummy->previous;

        prevPtr->next = new;
        new->next = dummy;
        new->previous = prevPtr;
        dummy->previous = new;
    }
}

void dealCards(Board* board, Card* cards[]) {
    cards[0]->isFlipped = true;
    insertNext(board->columns[0], cards[0]);

    int count = 1;

    for (int i = 1; i < 7; i++ ) {
        for (int j = 1; j < i; j++) {
            // Åbne kort
            cards[count]->isFlipped = true;
            insertNext(board->columns[j], cards[count]);
            count++;
        }

        for (int k = i; k < 7; k++) {
            // Lukkede kort
            insertNext(board->columns[k], cards[count]);
            count++;
        }
    }

    for (int i = 2; i < 6; i++ ) {

        for (int j = i; j < 7; j++) {
            // Resterende åbne kort
            cards[count]->isFlipped = true;
            insertNext(board->columns[j], cards[count]);
            count++;
        }
    }

    cards[count]->isFlipped = true;
    insertNext(board->columns[6], cards[count]);
}