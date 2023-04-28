#include "card.h";

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