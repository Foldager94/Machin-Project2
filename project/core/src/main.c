#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "card.h"

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
    return 0;

}

Card** createDeck(char charCardArray[3]){
    int arraySize = sizeof(charCardArray)/sizeof(charCardArray[0]);
    for(int i =0; i < arraySize; i++){

    };
}

Card* createCard(char cardSuit, char cardValue){
    Card* newCard = malloc(sizeof(Card));
    newCard->isFlipped = false;
    newCard->cardValue = cardValue;
    newCard->cardSuit = cardSuit;
    newCard->previous = NULL;
    newCard->next = NULL;
    return newCard;
}



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