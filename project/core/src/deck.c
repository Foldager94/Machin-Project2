#include "deck.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define NUM_CARDS 52
#define defaultPath "../project/core/src/unshuffled_deck.txt"
#define stringSize 156


char* loadFile(char filePath[]){
    setlocale(LC_ALL, "UTF-8");
    FILE *fp;
    if(filePath == NULL){
        fp = fopen(defaultPath, "r");
    }else{
        fp = fopen(filePath, "r");
    }
   
    //checks if the file is open correctly
    if (fp == NULL) { 
        printf("Error opening the file\n");
        return NULL;
    };

    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    rewind(fp);
    char* stringDeck = (char*) malloc(stringSize+1);
    fread(stringDeck, sizeof(char), file_size, fp);
    fclose(fp);

    for (int i = 0; i < file_size; i++) {
        if (stringDeck[i] == '\n') {
            stringDeck[i] = ' ';
        }
    }

    return stringDeck;
};

#define NUM_CARDS_ONE_DECK 52

Card *createDeck(char* stringDeck) {
    Card *deck = NULL;
    Card *currentCard = NULL;
    Card *previousCard = NULL;

    // Init dummy card
    deck = init_list();

    previousCard = deck;

    // Find length of the stringDeck
    // It divids by 4 since each card in a file is representet by 3 chars and 1 whitespace
    int numCards = strlen(stringDeck) / 3;

    // Checks if the file contains 52 cards, returns null and print error if it is more or less then
    if(numCards != NUM_CARDS_ONE_DECK){
        printf("Error in deck: This is not a complete set of 52 cards.\n");
        return NULL;
    }


    // Creats each card in the order that is given in the file
    for (int i = 0; i < numCards; i++){
        currentCard = init_list();
        currentCard->cardValue = stringDeck[i*3];
        currentCard->cardSuit = stringDeck[i*3+1];
        currentCard->previous = previousCard;
        currentCard->next = NULL;

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
        printf("%c%c ", currentCard->cardValue, currentCard->cardSuit);
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

    Card *pileOne = init_list();
    Card *pileTwo = init_list();
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
    Card *unshuffledDeck = init_list();
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

char* deckToString(Card *deck, bool sperateWithNewLine){
    int deckSize = deckLength(deck);
    int stringLength = deckSize*3;
    char *resultString = malloc(stringLength);
    Card *currentCard = deck ->next;
    char tmpString[4];
    for(int i = 0; i < deckSize; i++){
        if(currentCard->cardSuit==' '){
            break;
        }
        if(sperateWithNewLine) {
            sprintf(tmpString, "%c%c%c", currentCard->cardValue, currentCard->cardSuit, '\n');
        }else{
            sprintf(tmpString, "%c%c%c", currentCard->cardValue, currentCard->cardSuit, ' ');
        }
        if(i == 0){
            strcpy(resultString,tmpString);
        }else{

            strcat(resultString,tmpString);
        }
        currentCard = currentCard->next;
    };
    return resultString;
}

int saveDeckToFile(Card *deck, char* fileName){
    int deckSize = deckLength(deck);
    int stringLength = deckSize*3;
    char *resultString = malloc(stringLength);
    Card *currentCard = deck ->next;
    char tmpString[4];
    for(int i = 0; i < deckSize; i++){
        if(currentCard->cardSuit==' '){
        }
        sprintf(tmpString, "%c%c%c", currentCard->cardValue, currentCard->cardSuit, '\n');
        if(i == 0){
            strcpy(resultString,tmpString);
        }else{

            strcat(resultString,tmpString);
        }
        currentCard = currentCard->next;
    };

    FILE *fp;
    fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("saveDeckToFile: Error opening the file\n");
        return 1;
    };
    fprintf(fp, "%s", resultString);
    free(resultString);
    return 0;
}

void freeDeck(Card *deck) {
    Card *currentCard = deck->next;
    while (currentCard != deck) {
        Card *temp = currentCard;
        currentCard = currentCard->next;
        free(temp);
    }
    free(deck);
}