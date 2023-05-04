#ifndef CARD_H
#define CARD_H

#include <stdbool.h>

extern const int CARD_A;
extern const int CARD_2;
extern const int CARD_3;
extern const int CARD_4;
extern const int CARD_5;
extern const int CARD_6;
extern const int CARD_7;
extern const int CARD_8;
extern const int CARD_9;
extern const int CARD_T;
extern const int CARD_J;
extern const int CARD_Q;
extern const int CARD_K;

typedef struct card {
    bool isFlipped;
    char cardValue;
    char cardSuit;
    struct card *previous;
    struct card *next;
}Card;

extern void insert_next_in_list(Card* dummy, Card* new);
extern void insert_list_in_list(Card* dummy, Card* first, Card* last);
extern Card* pop_last_in_list(Card* dummy);
extern void clear_list(Card* dummy);
extern Card* init_list();

#endif