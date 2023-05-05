#include "deck.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define NUM_CARDS 52
#define defaultPath "../decks/unshuffled_deck.txt"
#define stringSize 208

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


char* loadFile(char filePath[]){
    char tmpStringDeck[stringSize];
    FILE *fp;
    if(filePath == NULL){
        fp = fopen(defaultPath, "r");
    }else{
        fp = fopen(filePath, "r");
    }
   
    //checks if the file is open correctly
    if (fp == NULL) { 
        printf("Fejl ved åbning af filen\n");
        return NULL;
    };
    
    fgets(tmpStringDeck, sizeof(tmpStringDeck), fp);
    char* stringDeck = (char*) malloc(sizeof(tmpStringDeck));
    strcpy(stringDeck, tmpStringDeck);
    fclose(fp);
    return stringDeck;
};

#define NUM_CARDS_ONE_DECK 52

Card *createDeck(char* stringDeck) {
    Card *deck = NULL;
    Card *currentCard = NULL;
    Card *previousCard = NULL;

    // Init dummy card
    deck = initCard();

    previousCard = deck;

    // Find length of the stringDeck
    // It divids by 4 since each card in a file is representet by 3 chars and 1 whitespace
    // Adds 1 to the count to compensate for the last cards missing whitespace
    int numCards = strlen(stringDeck) / 4 +1;

    // Checks if the file contains 52 cards, returns null and print error if it is more or less then
    if(numCards != NUM_CARDS_ONE_DECK){
        printf("Fejl i dækket: Dette er ikke et komplet sæt kort af 52\n");
        return NULL;
    }


    // Creats each card in the order that is given in the file
    for (int i = 0; i < numCards; i++){
        currentCard = initCard();
        currentCard->cardSuit = stringDeck[i*4];
        currentCard->cardValue = stringDeck[i*4+2];
        currentCard->previous = previousCard;

        previousCard->next = currentCard;
        previousCard = currentCard;
    };

    // Links first card (Dummy Card) to the last card
    currentCard->next = deck;
    deck->previous = currentCard;

    return deck;
};

void printDeck(Card *deck) {
    Card *currentCard = deck->next;
    printf("Deck:\n");
    while (true) {
        printf("%c%c ", currentCard->cardSuit, currentCard->cardValue);
        currentCard = currentCard->next;
        if(currentCard->cardSuit == ' '){
            break;
        };
    }
    printf("\n\n");
};

int deckLength(Card* deck) {
    int count = 0;
    Card* current = deck;
    while (true) {
        count++;
        current = current->next;
        if(current == deck){
            break;
        }
    }
    return count-1;
};

int shuffleDeck(Card* deck, int split){

    Card *pileOne = initCard();
    Card *pileTwo = initCard();
    Card* currentCard = deck->next;

    //Divide the deck in to to piles based on split value
    for(int i = 0; i < split; i++){
        currentCard = currentCard->next;
    };

    pileOne->next = deck->next;
    pileOne->previous = currentCard->previous;

    pileTwo->next = currentCard;
    pileTwo->previous = deck->previous;

    pileOne->previous->next = pileOne;
    pileTwo->previous->next = pileTwo;

    // printDeck(pileOne);
    // printDeck(pileTwo);

    Card *deckTopCard = deck;
    Card *pileOneCurrentCard = pileOne->next;
    Card *pileTwoCurrentCard = pileTwo->next;
    Card *pileOneNextCard;
    Card *pileTwoNextCard;

    // TODO: Comment
    while(true){
        if(pileOneCurrentCard->cardValue != ' ' && pileTwoCurrentCard->cardValue != ' '){
            pileOneNextCard = pileOneCurrentCard->next;
            pileTwoNextCard = pileTwoCurrentCard->next;

            deckTopCard->next = pileOneCurrentCard;
            pileOneCurrentCard->next = pileTwoCurrentCard;
            pileTwoCurrentCard->next = deck;

            pileOneCurrentCard->previous = deckTopCard;
            pileTwoCurrentCard->previous = pileOneCurrentCard;
            deck->previous = pileTwoCurrentCard;

            deckTopCard = pileTwoCurrentCard;

            pileOneCurrentCard = pileOneNextCard;
            pileTwoCurrentCard = pileTwoNextCard;
        } else if(pileOneCurrentCard->cardValue != ' '){
            pileOneNextCard = pileOneCurrentCard->next;

            deckTopCard->next = pileOneCurrentCard;
            pileOneCurrentCard->previous = deckTopCard;

            pileOneCurrentCard->next = deck;
            deck->previous = pileOneCurrentCard;

            deckTopCard = pileOneCurrentCard;

            pileOneCurrentCard = pileOneNextCard;
        } else if(pileTwoCurrentCard->cardValue != ' '){
            pileTwoNextCard = pileTwoCurrentCard->next;

            deckTopCard->next = pileTwoCurrentCard;
            pileTwoCurrentCard->previous = deckTopCard;

            pileTwoCurrentCard->next = deck;
            deck->previous = pileTwoCurrentCard;

            deckTopCard = pileTwoCurrentCard;

            pileTwoCurrentCard = pileTwoNextCard;
        } else {
            break;
        };
    };

    return 0;
};

int shuffleDeckRandom(Card* deck){
    int deckSize = deckLength(deck);
    Card *unshuffledDeck = initCard();
    unshuffledDeck->next = deck->next;
    unshuffledDeck->previous = deck->previous;

    deck->next = deck;
    deck->previous = deck;

    Card *currentCard = unshuffledDeck->next;
    Card *nextCard;
    Card *cardOnIndex = deck->next;
    int cardIndexPlacement;

    for (int i=1; i <=deckSize; i++){
        cardIndexPlacement = randomNumber(i)+1;
        for (int j=1; j<=cardIndexPlacement; j++){
            cardOnIndex = cardOnIndex->next;
        };
        nextCard = currentCard->next;
        currentCard->next = cardOnIndex->next;
        cardOnIndex->next = currentCard;
        currentCard->previous = cardOnIndex;

        currentCard = nextCard;

    };
    return 0;
};