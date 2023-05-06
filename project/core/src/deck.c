#include "deck.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "card.h"
#define NUM_CARDS 52
#define defaultPath "../project/core/src/unshuffled_deck.txt"
#define stringSize 155
#define LINE_SIZE 3


Card* load_deck(char filePath[]){
    //setlocale(LC_ALL, "UTF-8");
    FILE *fp;
    if(filePath == NULL){
        fp = fopen(defaultPath, "r");
    }else{
        fp = fopen(filePath, "r");
    }
   
    //checks if the file is open correctly
    if (fp == NULL) {
        return NULL;
    }

    //fseek(fp, 0, SEEK_END);
    //int file_size = ftell(fp);
    //rewind(fp);
    //char* stringDeck = (char*) malloc(stringSize+1);
    //fread(stringDeck, sizeof(char), file_size, fp);*/

    Card* deck = init_list();
    char read[LINE_SIZE + 1];

    while (!feof(fp)) {
        if (fgets (read, sizeof(read), fp) != NULL) {
            Card* card = (Card*) malloc(sizeof(Card));
            card->cardValue = read[0];
            card->cardSuit = read[1];
            card->isFlipped = false;
            insert_next_in_list(deck, card);
        }
    }

    fclose(fp);
    return deck;

    //return stringDeck;
}

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
    if(fileName == NULL){
        fp = fopen("cards.txt", "w");
    } else{
        fp = fopen(fileName, "w");
    }
    if (fp == NULL) {
        printf("saveDeckToFile: Error opening the file\n");
        return 1;
    };
    fprintf(fp, "%s", resultString);
    free(resultString);
    fclose(fp);
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