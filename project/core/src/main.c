#include <stdio.h>
#include <malloc.h>
#include "board.h"
#include "card.h"

#define MIN_LINE_PRINT 8
#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void printBoard(struct board, bool showAll);

int main() {

    struct board gameBoard;

    for (int i = 0; i < COL_COUNT; i++) {
        Card *dummy;
        dummy = (Card*)malloc(sizeof(Card));

        dummy->cardValue = ' ';
        dummy->previous = dummy;
        dummy->next = dummy;
        gameBoard.columns[i] = dummy;
    }

    Card *t;
    t = (Card*) malloc(sizeof(Card));
    t->cardValue = '3';
    t->cardSuit = 'H';

    Card *x;
    x = (Card*) malloc(sizeof(Card));
    x->cardValue = '7';
    x->cardSuit = 'H';
    x->isFlipped = true;

    insertNext(gameBoard.columns[0], t);
    insertNext(gameBoard.columns[0], x);

    for (int i = 0; i < FOUNDATION_COUNT; i++) {
        Card *dummy;
        dummy = (Card*)malloc(sizeof(Card));

        dummy->cardValue = ' ';
        dummy->previous = dummy;
        dummy->next = dummy;
        gameBoard.foundations[i] = dummy;
    }

    printBoard(gameBoard, true);

    return 0;

}

void printBoard(struct board gameBoard, bool showAll) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\n\n");

    int emptyCounter = 0;
    int counter = 0;
    int foundationCounter = 0;

    // Pointers to each column card
    Card* cards[COL_COUNT];
    for (int i = 0; i < COL_COUNT; i++) {
        cards[i] = gameBoard.columns[i]->next;
    }

    while (counter < MIN_LINE_PRINT || emptyCounter < COL_COUNT) {

        // Print from each column
        for (int i = 0; i < COL_COUNT; i++) {
            Card* current = cards[i];
            if (current->cardValue == ' ') {
                printf("  ");
                emptyCounter++;
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
        if ((counter & 1) && (counter < (FOUNDATION_COUNT * 2))) {
            Card* fCard = gameBoard.foundations[foundationCounter]->previous;
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

    printf("\nLAST Command:\nMessage:\nINPUT >");
}