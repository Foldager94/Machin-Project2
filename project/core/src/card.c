#include <stdlib.h>
#include <time.h>
#include "card.h"

// ASCII decimal values from card values
const int CARD_A = 65;
const int CARD_T = 84;
const int CARD_J = 74;
const int CARD_Q = 81;
const int CARD_K = 75;

//Convert ASCII to numeric values including edge cases for A,T,Q,K as 1,10,11,12,13
int ASCII_to_numeric(int cardValue) {
    if (cardValue == CARD_A) {
        return 1;
    } else if (cardValue == CARD_T) {
        return 10;
    } else if (cardValue == CARD_J) {
        return 11;
    } else if (cardValue == CARD_Q) {
        return 12;
    } else if (cardValue == CARD_K) {
        return 13;
    } else {
        return cardValue - 48;
    }
}

// Generates random number, based on current time seed
int randomNumber(int max){
    // Sets a random seed for the Rand function
    srand(time(NULL));
    // Finds a random number between 0 and max
    int randomInt = rand() % max;
    //printf("RandomInt: %d\n", randomInt);
    return randomInt;
};

//Go through a column and search for a specific card if the card exists and is flipped it is return else dummy is returned
Card* find_card(Card* dummy, char thisCardValue, char thisCardSuit ) {
    Card* returnCard = dummy;
    Card* current = dummy;

    bool moreCards = true;
    while (moreCards) {
        current = current->previous;
        if (current->cardValue == ' ') {
            moreCards = false;
            break;
        } else if (!current->isFlipped) {
            moreCards = false;
            break;
        } else {
            if (current->cardValue == thisCardValue && current->cardSuit == thisCardSuit) {
                returnCard == current;
                moreCards = false;
                break;
            }
        }
    }
    return returnCard;
}


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

// Removes all cards from the bottom of the list to the selected target (use with insert_list_in_list to perform a move)
void remove_list_in_list(Card* dummy, Card* target) {
    Card* new_last = dummy->previous;
    while (new_last != target && new_last != dummy) {
        new_last = new_last->previous;
    }

    // Ensure that target was actually found, otherwise do nothing
    if (new_last->cardValue != ' ') {
        new_last = new_last->previous;
        new_last->next = dummy;
        dummy->previous = new_last;

        // Fix dummy's next pointer, if column is now empty
        if (dummy->next == target) {
            dummy->next = dummy;
        }
    }
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

// Creates a copy of a given card linked list in source to destination (destination should be after init_list)
void make_copy(Card* source, Card* destination) {
    Card* current = source->next;
    while (current->cardValue != ' ') {
        Card* copy = (Card*) malloc(sizeof(Card));
        copy->cardValue = current->cardValue;
        copy->cardSuit = current->cardSuit;
        copy->isFlipped = current->isFlipped;
        copy->previous = NULL;
        copy->next = NULL;
        insert_next_in_list(destination, copy);
        current = current->next;
    }
}