#ifndef CARD_H
#define CARD_H

#include <stdbool.h>

typedef struct card {
    bool isFlipped;
    char cardValue;
    char cardSuit;
    struct card *previous;
    struct card *next;
}Card;

#endif