#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "board.h"
#include "card.h"
#include "commandLine.h"
#include "deck.h"
#include <time.h>
#include <stdbool.h>

#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void printCommandLine(CommandLine*);

void TEST_ASCII_to_numeric() {

    //ASCII_to_numeric 1
    int expected = 1;
    if (ASCII_to_numeric(65) == expected) {
        printf("ASCII_to_numeric 1: PASSED");
    } else {
        printf("ASCII_to_numeric 1: Failed");
    }
}

int main() {

//     Board gameBoard;
//     CommandLine commandLine;

//     //Initialize dummy elements
//     for (int i = 0; i < COL_COUNT; i++) {
//         gameBoard.columns[i] = init_list();
//     }

//     for (int i = 0; i < FOUNDATION_COUNT; i++) {
//         gameBoard.foundations[i] = init_list();
//     }

    //Initialize commands
    commandLine.command[0] = ' ';
    commandLine.message[0] = ' ';

    print_board(&gameBoard, false);
    printCommandLine(&commandLine);

//     bool isRunning = true;
//     bool gameStarted = false;
//     bool deckLoaded = false;
//     Card* deck;

//     while (isRunning) {
//         char input[101];
//         fgets(input,sizeof(input),stdin);

//             if (input[0] == 'L' && input[1] == 'D') { //LD command
//                 if (gameStarted) {
//                     strcpy(commandLine.command, "LD");
//                     strcpy(commandLine.message, "Command not available in the PLAY phase");

//                 } else {
//                     if (input[2] == '\n') {
//                         //No file specified
//                     } else {
//                         //file specified
//                     }
//                     deckLoaded = true;

//                 }

//                 //Print stuff

//             } else if (input[0] == 'S' && input[1] == 'W') { //SW command
//                 bool commandSuccessfull = false;

//                 if (gameStarted) {
//                     strcpy(commandLine.command, "SW");
//                     strcpy(commandLine.message, "Command not available in the PLAY phase");
//                 } else {
//                     if (input[2] == '\n') {
//                         if (deckLoaded == false) {
//                             strcpy(commandLine.command, "SW");
//                             strcpy(commandLine.message, "ERROR no deck");

//                         } else {
//                             strcpy(commandLine.command, "SW");
//                             strcpy(commandLine.message, "ok");
//                             commandSuccessfull = true;
//                         }
//                     } else {
//                         strcpy(commandLine.command, " ");
//                         strcpy(commandLine.message, "Incorect command");
//                     }
//                 }
//                 printCommandLine(&commandLine);
//                 print_board(&gameBoard, commandSuccessfull);

//             } else if (input[0] == 'S' && input[1] == 'I') { //SI command
//                 if (input[2] == '\n') {
//                     //No split specified
//                 } else {
//                     //split specified
//                 }

//             } else if (input[0] == 'S' && input[1] == 'R') { //SR command


//             } else if (input[0] == 'S' && input[1] == 'D') { //SD command

//             } else if (input[0] == 'Q' && input[1] == 'Q') { //QQ command
//                 isRunning = false;

//             } else if (input[0] == 'P') { //P command
//                 if (input[1] == '\n') {
//                     if (gameStarted) {
//                         strcpy(commandLine.command, "SW");
//                         strcpy(commandLine.message, "Command not available in the PLAY phase");
//                     } else {
//                         if (!deckLoaded) {
//                             strcpy(commandLine.command, "P");
//                             strcpy(commandLine.message, "ERROR no deck");
//                         } else {
//                             gameStarted = true;
//                             deal_cards(&gameBoard, deck);
//                             strcpy(commandLine.command, "P");
//                             strcpy(commandLine.message, "OK");
//                         }
//                     }
//                 } else {
//                     strcpy(commandLine.command, " ");
//                     strcpy(commandLine.message, "Incorect command");
//                 }

//                 print_board(&gameBoard, false);
//                 printCommandLine(&commandLine);

//             } else if (input[0] == 'Q') {
//                 if (input[1] == '\n') {
//                     if (gameStarted) {
//                         gameStarted = false;

//                         //reload the deck
//                     } else {
//                         strcpy(commandLine.command, "Q");
//                         strcpy(commandLine.message, "Command not available in the STARTUP phase");
//                     }
//                 } else {
//                     strcpy(commandLine.command, " ");
//                     strcpy(commandLine.message, "Incorect command");
//                 }

//                 print_board(&gameBoard, false);
//                 printCommandLine(&commandLine);

            } else if (input[0] == 'C' ) { //Move command
                strcpy(commandLine.command, " ");
                strcpy(commandLine.message, "Incorect command");

                if (input[1] == '1' || input[1] == '2' || input[1] == '3' || input[1] == '4' || input[1] == '5' || input[1] == '6' || input[1] == '7') {
                    Card* fromColumn = gameBoard.columns[ASCII_to_numeric((int) input[1])-1];         //Save the column to move from

                    if (input[2] == ':'){
                        Card* toMove = find_card(fromColumn, input[3], input[4]);
                        if (toMove->cardValue != ' ') {
                            if (input[5] == '-' && input[6] == '>') {
                                if (input[7] == 'F') {
                                    if (toMove->next->cardValue == ' ') {  //Make sure it is the bottom card
                                        if (input[8] == '1' || input[8] == '2' || input[8] == '3' || input[8] == '4') {
                                            Card* destination = gameBoard.foundations[ASCII_to_numeric((int) input[8])-1]->previous;

                                            //Validate move
                                            if (destination->cardSuit == toMove->cardSuit && ASCII_to_numeric((int)destination->cardValue) - ASCII_to_numeric((int)toMove->cardValue) == -1 ) {
                                                //Preform move to Foundation
                                                toMove = pop_last_in_list(fromColumn);
                                                insert_next_in_list(destination->next, toMove);


                                                char msg[30];
                                                sprintf(msg,"C%c:%c%c->F%c", input[1],input[3],input[4],input[8]);
                                                strcpy(commandLine.command, msg);
                                                strcpy(commandLine.message, "OK");
                                            }
                                        }
                                    }
                                } else if (input[7] == 'C') {
                                    if (input[8] == '1' || input[8] == '2' || input[8] == '3' || input[8] == '4' || input[8] == '5' || input[8] == '6' || input[8] == '7') {
                                        Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[8])-1]->previous;

                                        //Validate move
                                        if (destination->cardSuit != toMove->cardSuit && ASCII_to_numeric((int)destination->cardValue) - ASCII_to_numeric((int)toMove->cardValue) == 1 ) {

                                            //Make move

                                            char msg[30];
                                            sprintf(msg,"C%c:%c%c->C%c", input[1],input[3],input[4],input[8]);
                                            strcpy(commandLine.command, msg);
                                            strcpy(commandLine.message, "OK");

                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (input[2] == '-' && input[3] == '>') {
                            if (input[4] == 'F') {
                                if (input[5] == '1' || input[5] == '2' || input[5] == '3' || input[5] == '4') {
                                    Card* destination = gameBoard.foundations[ASCII_to_numeric((int) input[5])-1]->previous;

                                    if (destination->cardSuit == fromColumn->previous->cardSuit && ASCII_to_numeric((int)destination->cardValue) - ASCII_to_numeric((int)fromColumn->previous->cardValue) == -1 ) {

                                        //Move card
                                        Card* toMove = pop_last_in_list(fromColumn);
                                        insert_next_in_list(destination->next, toMove);

                                        char msg[30];
                                        sprintf(msg,"C%c->F%c", input[1],input[5]);
                                        strcpy(commandLine.command, msg);
                                        strcpy(commandLine.message, "OK");
                                    }
                                }
                            } else if (input[4] == 'C') {
                                if (input[5] == '2' || input[5] == '3' || input[5] == '4' || input[5] == '5' || input[5] == '6' || input[5] == '7') {
                                    Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[5])-1]->previous;

                                    if (destination->cardSuit != fromColumn->previous->cardSuit && ASCII_to_numeric((int)destination->cardValue) - ASCII_to_numeric((int)fromColumn->previous->cardValue) == 1 ) {

                                        //Move card
                                        Card* toMove = pop_last_in_list(fromColumn);
                                        insert_next_in_list(destination->next, toMove);

                                        char msg[30];
                                        sprintf(msg,"C%c->C%c", input[1],input[5]);
                                        strcpy(commandLine.command, msg);
                                        strcpy(commandLine.message, "OK");
                                    }
                                }

                            }
                        }
                    }

                }




            } else if (input[0] == 'F') { //Move from faundation
                if (input[1] == '1' || input[1] == '2' || input[1] == '3' || input[1] == '4') { //The FROM is recognized
                    if (input[2] == '-' && input[3] == '>') { //Midle is recognized
                        if (input[4] == 'C' && input[5] == '1' || input[5] == '2' || input[5] == '3' || input[5] == '4' || input[5] == '5' || input[5] == '6' || input[5] == '7') { //To is recognized
                            Card* toMove = gameBoard.foundations[ASCII_to_numeric((int) input[1])-1]->previous;
                            Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[5])-1]->previous;

                            //Check if piles are empty
                            if (destination->cardValue == ' ' || toMove->cardValue == ' ') {
                                strcpy(commandLine.command, " ");
                                strcpy(commandLine.message, "Invalid move");
                            } else {
                                //Validate the move
                                if (destination->cardSuit != toMove->cardSuit && ASCII_to_numeric((int)destination->cardValue) - ASCII_to_numeric((int)toMove->cardValue) == 1 )  {
                                    //if valid move the card
                                    toMove = pop_last_in_list(toMove->next);
                                    insert_next_in_list(destination->next, toMove);

                                    char msg[30];
                                    sprintf(msg,"F%c->C%c", toMove->cardValue, destination->cardValue);
                                    strcpy(commandLine.command, msg);
                                    strcpy(commandLine.message, "OK");
                                } else {
                                    strcpy(commandLine.command, " ");
                                    strcpy(commandLine.message, "Invalid move");
                                }
                            }
                        } else {
                            strcpy(commandLine.command, " ");
                            strcpy(commandLine.message, "Incorect command");
                        }
                    } else {
                        strcpy(commandLine.command, " ");
                        strcpy(commandLine.message, "Incorect command");
                    }
                } else {
                    strcpy(commandLine.command, " ");
                    strcpy(commandLine.message, "Incorect command");
                }

                 print_board(&gameBoard, false);
                 printCommandLine(&commandLine);

             } else { //unknown command
                 strcpy(commandLine.command, " ");
                 strcpy(commandLine.message, "Incorect command");
                 print_board(&gameBoard, false);
                 printCommandLine(&commandLine);
             }
         }

    TEST_ASCII_to_numeric();

    return 0;
}



//Print the commandline
void printCommandLine (CommandLine* commandLine) {
    if (commandLine->command[0] == ' ' && commandLine->message[0] == ' ' ) {
        printf("LAST Command: \n");
        printf("Message: \n");
        printf("INPUT > ");
    } else {
        printf("LAST Command: %s \n", commandLine->command);
        printf("Message: %s \n", commandLine->message);
        printf("INPUT > ");
    }
}



//
// fileLoader.c
//

#define defaultPath "../decks/unshuffled_deck.txt"
// 208 = 52*4
#define stringSize 208

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
}

Card* initCard(){
    Card *card = NULL;
    card = (Card*)malloc(sizeof(Card));
    card->isFlipped = false;
    card->cardValue = '0';
    card->cardSuit = '0';
    card->previous = NULL;
    card->next = NULL;

    return card;
}


//
// deck.c
//
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
}


void printDeck(Card *deck) {
    Card *currentCard = deck->next;
    printf("Deck:\n");
    while (true) {
        printf("%c%c ", currentCard->cardSuit, currentCard->cardValue);
        currentCard = currentCard->next;
        if(currentCard->cardSuit == '0'){
            break;
        };
    }
    printf("\n\n");
}


//
// LD command
//
Card* LD(char filePath[]){
    char* stringDeck = loadFile(NULL);
    Card *deck = createDeck(stringDeck);
    free(stringDeck);
    return deck;
};

int stringToInt(char* str) {
    int result = 0;
    int sign = 1;
    // Checks if the given string is negativ - Sets sign ti -1 if it is
    if (*str == '-') {
        sign = -1;
        str++;
    }
    // Iterates through the String, and adds its Ascii Value to result
    while (*str != '\0') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}

int randomNumber(int max){
    // Sets a random seed for the Rand function
    srand(time(NULL));
    // Finds a random number between 0 and max
    int randomInt = rand() % max;
    //printf("RandomInt: %d\n", randomInt);
    return randomInt;
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
}

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
        if(pileOneCurrentCard->cardValue != '0' && pileTwoCurrentCard->cardValue != '0'){
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
        } else if(pileOneCurrentCard->cardValue != '0'){
            pileOneNextCard = pileOneCurrentCard->next;

            deckTopCard->next = pileOneCurrentCard;
            pileOneCurrentCard->previous = deckTopCard;

            pileOneCurrentCard->next = deck;
            deck->previous = pileOneCurrentCard;

            deckTopCard = pileOneCurrentCard;

            pileOneCurrentCard = pileOneNextCard;
        } else if(pileTwoCurrentCard->cardValue != '0'){
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

//
// SL command
//
int SL(Card* deck, char* split){
    int splitInt;
    if(strcmp(split, "") == 0){
        splitInt = randomNumber(53);
    }else{
        splitInt = stringToInt(split);
        if(splitInt < 53 && 0 > splitInt){
            printf("Fejl: Tallet er 0 eller negativ, eller større end mængden af kort i dækket");
            return 1;
        }
    };
    shuffleDeck(deck, splitInt);
    return 0;
}


//
// SR
//
int SR(Card* deck){
    shuffleDeckRandom(deck);
    return 0;
}

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
}

//
// SD
//
int saveDeckToFile(Card *deck){
    int deckSize = deckLength(deck);
    int stringLength = deckSize*4;
    char *resultString = malloc(stringLength);
    Card *currentCard = deck ->next;
    char tmpString[4];
    for(int i = 0; i < deckSize; i++){
        if(currentCard->cardSuit=='0'){
        }
        sprintf(tmpString, "%c%c%c%c", currentCard->cardSuit, ':', currentCard->cardValue, ' ');
        if(i == 0){
            strcpy(resultString,tmpString);
        }else{

        strcat(resultString,tmpString);
        }
        currentCard = currentCard->next;
    printf("%s\n",resultString);
    };
}


int main() { 
    Card *deck = LD(NULL);
    SL(deck, "32");
    saveDeckToFile(deck);
    //printDeck(deck);
    return 0;
};