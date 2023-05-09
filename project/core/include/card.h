#ifndef CARD_H
#define CARD_H

#include <stdbool.h>

extern const int CARD_A;
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

extern void insertNextInList(Card* dummy, Card* new);
extern void insertListInList(Card* dummy, Card* first, Card* last);
extern Card* popLastInList(Card* dummy);
extern void clearList(Card* dummy);
extern Card* initList();
extern int asciiToNumeric(int cardValue);
extern Card* findCard(Card* dummy, char thisCardSuit, char thisCardValue);
extern int randomNumber(int max);
extern void makeCopy(Card* source, Card* destination);
extern void removeListInList(Card* dummy, Card* target);
#endif