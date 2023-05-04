#include <stdlib.h>

#include "card.h"

// ASCII decimal values from card values
const int CARD_A = 65;
const int CARD_2 = 50;
const int CARD_3 = 51;
const int CARD_4 = 52;
const int CARD_5 = 53;
const int CARD_6 = 54;
const int CARD_7 = 55;
const int CARD_8 = 56;
const int CARD_9 = 57;
const int CARD_T = 84;
const int CARD_J = 74;
const int CARD_Q = 81;
const int CARD_K = 75;

void insert_next_in_list(Card* dummy, Card* new) {
    Card *prevPtr = dummy->previous;
    prevPtr->next = new;
    new->next = dummy;
    new->previous = prevPtr;
    dummy->previous = new;
}

// Insert linked list of cards into the bottom of exists linked list (game logic)
void insert_list_in_list(Card* dummy, Card* first, Card* last) {
    Card *prevPtr = dummy->previous;
    prevPtr->next = first;
    last->next = dummy;
    first->previous = prevPtr;
    dummy->previous = last;
}

Card* init_list() {
    Card *dummy = (Card*)malloc(sizeof(Card));
    dummy->isFlipped = false;
    dummy->cardSuit = ' ';
    dummy->cardValue = ' ';
    dummy->previous = dummy;
    dummy->next = dummy;
    return dummy;
}

// Clear all elements in the linked list
// This will also free the memory allocated
void clear_list(Card* dummy) {
    Card* previousPtr = dummy->previous;
    while (previousPtr->cardValue != ' ') {
        Card* prevPreviousPtr = previousPtr->previous;
        free(previousPtr);
        previousPtr = prevPreviousPtr;
    }

    dummy->previous = dummy;
    dummy->next = dummy;
}

// Pop the last card pushed into the linked list (use for game logic)
// This function does not free any memory, but removes the links in the linked list and returns the pointer to the card
Card* pop_last_in_list(Card* dummy) {
    Card* popped = dummy->previous;

    // Check if the list is empty
    if (popped == dummy) {
        return dummy;
    }

    // Check if popped card is last in linked list (except dummy)
    if (popped->previous == dummy) {
        dummy->previous = dummy;
        dummy->next = dummy;
        return popped;
    }

    Card* new_last = popped->previous;
    new_last->next = dummy;
    dummy->previous = new_last;

    return popped;
}