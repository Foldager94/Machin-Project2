#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "board.h"

#define MIN_LINE_PRINT 8
#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void insert_next(Card* dummy, Card* new) {
    Card *prevPtr = dummy->previous;
    prevPtr->next = new;
    new->next = dummy;
    new->previous = prevPtr;
    dummy->previous = new;
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

void deal_cards(Board* board, Card* deck) {
    // First card goes in the first column
    deck->isFlipped = true;
    insert_next(board->columns[0], deck);

    Card* nextCard = deck->next;
    for (int i = 1; i < 7; i++ ) {
        for (int j = 1; j < i; j++) {
            // Deal the open cards
            nextCard->isFlipped = true;
            insert_next(board->columns[j], nextCard);
            nextCard = nextCard->next;
        }

        for (int k = i; k < 7; k++) {
            // Deal the closed cards
            insert_next(board->columns[k], nextCard);
            nextCard = nextCard->next;
        }
    }

    for (int i = 2; i < 6; i++ ) {
        for (int j = i; j < 7; j++) {
            // Deal remaining open cards in diagonal
            nextCard->isFlipped = true;
            insert_next(board->columns[j], nextCard);
            nextCard = nextCard->next;
        }
    }

    // Last open card in the last column
    nextCard->isFlipped = true;
    insert_next(board->columns[6], nextCard);
}

//Print the board with the current cards
void print_board(Board* board, bool showAll) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\n\n");

    int emptyCounter = 0;
    bool emptyColumns[7] = { false, false, false, false, false, false, false};
    int counter = 0;
    int foundationCounter = 0;

    // Pointers to each column card
    Card* cards[COL_COUNT];
    for (int i = 0; i < COL_COUNT; i++) {
        cards[i] = board->columns[i]->next;
    }

    while (counter < MIN_LINE_PRINT || emptyCounter < COL_COUNT) {

        // Print from each column
        for (int i = 0; i < COL_COUNT; i++) {
            Card* current = cards[i];
            if (current->cardValue == ' ') {
                printf(" ");
                if (!emptyColumns[i]) {
                    emptyColumns[i] = true;
                    emptyCounter++;
                }
            } else {
                if (!current->isFlipped && !showAll) {
                    printf("[]");
                } else {
                    printf("%c%c", current->cardValue, current->cardSuit);
                }
                cards[i] = current->next;
            }
            printf("\t");
        }

        // Print the foundations on the right side
        if (((counter & 1) == 0) && (counter < (FOUNDATION_COUNT * 2))) {
            Card* fCard = board->foundations[foundationCounter]->previous;
            if (fCard->cardValue != ' ') {
                printf("\t%c%c\tF%i", fCard->cardValue, fCard->cardSuit, foundationCounter + 1);
            } else {
                printf("\t[]\tF%i", foundationCounter + 1);
            }

            foundationCounter++;
        }

        printf("\n");
        counter++;
    }
}