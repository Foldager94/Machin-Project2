#ifndef DECK_H
#define DECK_H

#include "card.h"

Card *createDeck(char* stringDeckArray);
void printDeck(Card *deck);

extern char* loadFile(char filePath[]);
extern Card *createDeck(char* stringDeck);
extern void printDeck(Card *deck);
extern int deckLength(Card* deck);
extern int shuffleDeck(Card* deck, int split);
extern int shuffleDeckRandom(Card* deck);
extern int saveDeckToFile(Card *deck, char* fileName);
#endif /* DECK_H */