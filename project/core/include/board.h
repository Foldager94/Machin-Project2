#ifndef BOARD_H
#define BOARD_H

#include "card.h"

#define NUM_COLUMNS 7
#define NUM_FOUNDATIONS 4

typedef struct board {
    Card* columns[NUM_COLUMNS];
    Card* foundations[NUM_FOUNDATIONS];
}Board;

extern void dealCards(Board* board, Card* deck);
extern void printBoard(Board* board, bool showAll);
extern void placeDeck(Board* board, Card* deck);
extern Board* makeBoardCopy(Board* source);

#endif