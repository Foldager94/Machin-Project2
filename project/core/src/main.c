#include <stdio.h>
#include "board.h"

<<<<<<< HEAD
void printBoard() {
    printf("C1 \t C2 \t C3 \t C4 \t C5 \t C6 \t C7 \t \t ");
}

int main() {

    printBoard();
=======
#define MIN_LINE_PRINT 8
#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void printBoard(struct board);

int main() {

    struct board gameBoard;
    struct card c;
    c.cardSuit = 'H';
    c.cardValue = '3';
    c.isFlipped = false;
    gameBoard.columns[0] = c;

    printBoard(gameBoard);
>>>>>>> origin/main
    return 0;

}

<<<<<<< HEAD
=======
void printBoard(struct board gameBoard) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\n\n");

    int emptyCounter = 0;
    int counter = 0;

    struct card* cards[COL_COUNT];
    for (int i = 0; i < COL_COUNT; i++) {
        cards[i] = &gameBoard.columns[i];
    }

    while (counter < MIN_LINE_PRINT && emptyCounter < COL_COUNT) {

        for (int i = 0; i < COL_COUNT; i++) {
            struct card* current = cards[i];
            if (current->cardValue == "") {
                printf("  ");
                emptyCounter++;
            } else {
                if (gameBoard.columns[i].isFlipped) {
                    printf("[]");
                } else {
                    printf("%c%c", current->cardValue, current->cardSuit);
                }
            }
            printf("\t\n");
        }

        for (int i = 0; i < COL_COUNT; i++) {
            if (cards[i]->cardValue != "") {
                cards[i] = cards[i]->previous;
            }
        }

        counter++;
    }

    printf("\nLAST Command:\nMessage:\nINPUT >");
}
>>>>>>> origin/main
