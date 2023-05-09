#include <stdio.h>
#include <stdlib.h>
#include "../include/card.h"
#include "../include/board.h"

#define DECK_SIZE 52
#define MIN_LINE_PRINT 8
#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void dealCards(Board* board, Card* deck) {
    // First card goes in the first column
    deck->isFlipped = true;

    Card* current = deck->next;
    Card* nextCard = current->next;

    current->isFlipped = true;
    insertNextInList(board->columns[0], current);

    current = nextCard;
    nextCard = current->next;

    for (int i = 1; i < 7; i++ ) {
        for (int j = 1; j < i; j++) {
            // Deal the open cards
            current->isFlipped = true;
            insertNextInList(board->columns[j], current);

            current = nextCard;
            nextCard = current->next;
        }

        for (int k = i; k < 7; k++) {
            // Deal the closed cards
            insertNextInList(board->columns[k], current);

            current = nextCard;
            nextCard = current->next;
        }
    }

    for (int i = 2; i < 6; i++ ) {
        for (int j = i; j < 7; j++) {
            // Deal remaining open cards in diagonal
            current->isFlipped = true;
            insertNextInList(board->columns[j], current);

            current = nextCard;
            nextCard = current->next;
        }
    }

    // Last open card in the last column
    current->isFlipped = true;
    insertNextInList(board->columns[6], current);

    deck->next = deck;
    deck->previous = deck;
}

void placeDeck(Board* board, Card* deck) {
    Card* current = deck->next;
    Card* nextCard = current->next;
    for (int i = 0; i < DECK_SIZE; i++) {
        int currentColumn = i % COL_COUNT;
        insertNextInList(board->columns[currentColumn], current);
        current = nextCard;
        nextCard = current->next;
    }

    deck->next = deck;
    deck->previous = deck;
}

//Print the board with the current cards
void printBoard(Board* board, bool showAll) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\n\n");

    int emptyCounter = 0;
    bool emptyColumns[COL_COUNT] = { false, false, false, false, false, false, false};
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

Board* makeBoardCopy(Board* source) {
    Board* newBoard = malloc(sizeof(Board));
    // Copy columns
    for (int i = 0; i < COL_COUNT; i++) {
        Card* tmp_card = initList();
        makeCopy(source->columns[i], tmp_card);

        newBoard->columns[i] = tmp_card;

    }

    // Copy foundations
    for (int i = 0; i < FOUNDATION_COUNT; i++) {

        Card* tmp_card = initList();
        makeCopy(source->foundations[i], tmp_card);
        newBoard->foundations[i] = tmp_card;

    }
    return newBoard;
}