#ifndef DECK_H
#define DECK_H

#include "card.h"

#define NUM_OF_CARDS 52

typedef struct deck{
    Card *cards[NUM_OF_CARDS];
}Deck;

#endif
