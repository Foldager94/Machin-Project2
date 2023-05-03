#include "deck.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define NUM_CARDS 52

Card *createDeck(char* stringDeck) {
    Card *deck = NULL;
    Card *currentCard = NULL;
    Card *previousCard = NULL;

    // Init dummy card
    deck = (Card*)malloc(sizeof(Card));
    deck->isFlipped = false;
    deck->cardValue = '0';
    deck->cardSuit = '0';
    deck->previous = NULL;
    deck->next = NULL;

    previousCard = deck;
    // Find length of the stringDeck
    int numCards = strlen(stringDeck) / 3;


    for (int i = 0; i < numCards; i++){
        currentCard = (Card*)malloc(sizeof(Card));
        currentCard->isFlipped = false;
        currentCard->cardSuit = stringDeck[i*4];
        currentCard->cardValue = stringDeck[i*4+2];
        currentCard->previous = previousCard;
        currentCard->next = NULL;

        previousCard->next = currentCard;
        previousCard = currentCard;
    };

    currentCard->next = deck;
    deck->previous = currentCard;

    return deck;
}
void printDeck(Card *deck) {
    printf("Deck:\n");
    Card *currentCard = deck;
    int test = 0;
    while (test <= 52) {
        printf("%c%c ", currentCard->cardSuit, currentCard->cardValue);
        currentCard = currentCard->next;
        test++;
    }
    printf("\n");
}