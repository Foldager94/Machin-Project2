#ifndef BOARD_H
#define BOARD_H

#include "card.h"

#define NUM_COLUMNS 7
#define NUM_FOUNDATIONS 4

typedef struct board {
    Card *columns[NUM_COLUMNS];
    Card *foundations[NUM_FOUNDATIONS];
}Board;

extern void insert_next(Card* dummy, Card* new);
extern Card* init_list();
extern void clear_list(Card* dummy);
extern void deal_cards(Board* board, Card* deck);
extern void print_board(Board* board, bool showAll);

#endif