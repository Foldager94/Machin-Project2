#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "board.h"
#include "card.h"
#include "commandLine.h"
#include "deck.h"
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void printCommandLine(CommandLine*);



/*int SL(Card* deck, char* split){
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

int SR(Card* deck){
    shuffleDeckRandom(deck);
    return 0;
}*/

void TEST_ASCII_to_numeric() {

    //ASCII_to_numeric 1
    int expected = 1;
    if (ASCII_to_numeric(65) == expected) {
        printf("ASCII_to_numeric 1: PASSED");
    } else {
        printf("ASCII_to_numeric 1: Failed");
    }
}

void setCommandLine (CommandLine* commandLine, char msg[], char command[]) {
    strcpy(commandLine->message, msg);
    strcpy(commandLine->command, command);
}

bool validateColumn (char input) {
    if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5' || input == '6' || input == '7') {
        return true;
    } else return false;
}

bool validateFoundation (char input) {
    if (input == '1' || input == '2' || input == '3' || input == '4') {
        return true;
    } else return false;
}

bool validateMoveToFoundation (Card* toMove, Card* destination) {
    if (toMove->next->cardValue == ' ') {
        if (destination->cardValue == ' ' && toMove->cardValue == '1') {
            return true;
        } else if (destination->cardSuit == toMove->cardSuit && ASCII_to_numeric((int)destination->cardValue) - ASCII_to_numeric((int)toMove->cardValue) == -1 ) {
            return true;
        } else return false;
    } else return false;

}

bool validateMoveToColumn (Card* toMove, Card* destination) {
    if (destination->cardValue == ' ' && toMove->cardValue == 'K') {
        return true;
    } else if (destination->cardSuit != toMove->cardSuit && ASCII_to_numeric((int)destination->cardValue) - ASCII_to_numeric((int)toMove->cardValue) == 1 ) {
        return true;
    } else return false;
}

void moveSingleCard (Card* toMovColumn, Card* destination) {
    Card* toMove = pop_last_in_list(toMovColumn);
    insert_next_in_list(destination->next, toMove);
}


int main() {

    char NOT_AVAILABLE[] = "Command not available in the PLAY phase";
    char NO_DECK[] = "ERROR no deck";
    char ERROR[] = "ERROR unknown command";
    char OK[] = "Ok";

    Board gameBoard;
    Card* Deck;
    CommandLine commandLine;

    //Initialize dummy elements
    for (int i = 0; i < COL_COUNT; i++) {
        gameBoard.columns[i] = init_list();
    }

    for (int i = 0; i < FOUNDATION_COUNT; i++) {
        gameBoard.foundations[i] = init_list();
    }

    //Initialize commands
    commandLine.command[0] = ' ';
    commandLine.message[0] = ' ';

    print_board(&gameBoard, false);
    printCommandLine(&commandLine);

    bool isRunning = true;
    bool gameStarted = false;
    bool deckLoaded = false;
    Card* deck;

    while (isRunning) {
        bool showAll = false;
        char input[101];
        fgets(input,sizeof(input),stdin);

        char command[30];


            //Determening the input
            if (input[0] == 'L' && input[1] == 'D') { //LD command
                if (gameStarted) {

                    sprintf(command,"%c%c", input[0], input[1]);
                    strcpy(commandLine.command, command);
                    strcpy(commandLine.message, NOT_AVAILABLE);

                } else {
                    if (input[2] == '\n') {
                        //No file specified
                        char* stringDeck = loadFile(NULL);
                        Deck = createDeck(stringDeck);
                        free(stringDeck);

                    } else {
                        //file specified

                    }
                    deckLoaded = true;

                }



            } else if (input[0] == 'S' && input[1] == 'W') { //SW command

                if (gameStarted) {
                    setCommandLine(&commandLine, NOT_AVAILABLE, input);
                } else {
                    if (input[2] == '\n') {
                        if (deckLoaded == false) {
                            setCommandLine(&commandLine, NO_DECK, input);
                        } else {
                            setCommandLine(&commandLine, OK, input);
                            showAll = true;
                        }
                    } else {
                        setCommandLine(&commandLine, ERROR, input);
                    }
                }



            } else if (input[0] == 'S' && input[1] == 'I') { //SI command
                int splitInt;
                if (input[2] == '\0') {
                    //No split specified
                    splitInt = randomNumber(53);
                    shuffleDeck(deck, splitInt);
                } else {
                    //split specified

                }



            } else if (input[0] == 'S' && input[1] == 'R') { //SR command
                if (!gameStarted) {
                    shuffleDeckRandom(deck);
                }



            } else if (input[0] == 'S' && input[1] == 'D') { //SD command



            } else if (input[0] == 'Q' && input[1] == 'Q') { //QQ command
                if (!gameStarted) {
                    isRunning = false;
                } else {
                    setCommandLine(&commandLine,NOT_AVAILABLE,input);
                }



            } else if (input[0] == 'P') { //P command
                if (input[1] == '\n') {
                    if (gameStarted) {
                        setCommandLine(&commandLine, NOT_AVAILABLE, input);
                    } else {
                        if (!deckLoaded) {
                            setCommandLine(&commandLine, NO_DECK, input);
                        } else {
                            //Deal cards and start game
                            gameStarted = true;
                            deal_cards(&gameBoard, Deck);
                            setCommandLine(&commandLine, OK, input);
                        }
                    }
                } else {
                    setCommandLine(&commandLine, ERROR, input);
                }



            } else if (input[0] == 'Q') {
                if (input[1] == '\n') {
                    if (gameStarted) {
                        gameStarted = false;

                        //reload the deck
                    } else {
                        setCommandLine(&commandLine, NOT_AVAILABLE, input);
                    }
                } else {
                    setCommandLine(&commandLine, ERROR, input);
                }



            } else if (input[0] == 'C' ) { //Move command
                //Set defealt command and message
                setCommandLine(&commandLine, ERROR, input);

                if (validateColumn(input[1])) {
                    Card* fromColumn = gameBoard.columns[ASCII_to_numeric((int) input[1])-1];         //Save the column to move from

                    if (input[2] == ':'){
                        Card* toMove = find_card(fromColumn, input[3], input[4]);

                        if (toMove->cardValue != ' ') {
                            if (input[5] == '-' && input[6] == '>') {
                                if (input[7] == 'F') {
                                        if (validateFoundation(input[8])) {
                                            Card* destination = gameBoard.foundations[ASCII_to_numeric((int) input[8])-1]->previous;

                                            if (validateMoveToFoundation(toMove, destination)) {
                                                moveSingleCard(fromColumn,destination);
                                                setCommandLine(&commandLine, OK, input);
                                            }
                                        }
                                } else if (input[7] == 'C') {
                                    if (validateColumn(input[8])) {
                                        Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[8])-1]->previous;

                                        //Validate move
                                        if (validateMoveToColumn(toMove, destination)) {

                                            //Make move

                                            setCommandLine(&commandLine, OK, input);
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (input[2] == '-' && input[3] == '>') {
                            if (input[4] == 'F') {
                                if (validateFoundation(input[5])) {
                                    Card* destination = gameBoard.foundations[ASCII_to_numeric((int) input[5])-1]->previous;

                                    if (validateMoveToFoundation(fromColumn->previous, destination)) {
                                        moveSingleCard(fromColumn,destination);
                                        setCommandLine(&commandLine, OK, input);
                                    }
                                }
                            } else if (input[4] == 'C') {
                                if (validateColumn(input[5])) {
                                    Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[5])-1]->previous;

                                     if (validateMoveToColumn(fromColumn->previous, destination)) {
                                         moveSingleCard(fromColumn,destination);
                                         setCommandLine(&commandLine, OK, input);
                                    }
                                }
                            }
                        }
                    }

                }




            } else if (input[0] == 'F') { //Move from faundation
                //Set defealt command and message
                setCommandLine(&commandLine, ERROR, input);

                if (validateFoundation(input[1])) {
                    Card*  fromColumn = gameBoard.foundations[ASCII_to_numeric((int) input[1])-1];

                    if (input[2] == '-' && input[3] == '>') {
                        if (input[4] == 'C' && validateColumn(input[5])) {
                            Card* toMove = gameBoard.foundations[ASCII_to_numeric((int) input[1])-1]->previous;
                            Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[5])-1]->previous;

                            //Check if piles are empty
                            if (validateMoveToColumn(toMove, destination)) {
                                moveSingleCard(fromColumn,destination);

                                setCommandLine(&commandLine,OK,input);
                            }
                        }
                    }
                }
             }

            print_board(&gameBoard, showAll);
            printCommandLine(&commandLine);
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

        printf("LAST Command: ");
        int i = 0;
        char current = commandLine->command[i];
        while (current != '\n') {
            printf("%c", current);
            i ++;
            current = commandLine->command[i];
        }
        printf("\n");
        printf("Message: %s \n", commandLine->message);
        printf("INPUT > ");
    }
}



//
// fileLoader.c
//

// #define defaultPath "../decks/unshuffled_deck.txt"
// #define stringSize 208

// char* loadFile(char filePath[]){
//     char tmpStringDeck[stringSize];
//     FILE *fp;
//     if(filePath == NULL){
//         fp = fopen(defaultPath, "r");
//     }else{
//         fp = fopen(filePath, "r");
//     }
   
//     //checks if the file is open correctly
//     if (fp == NULL) { 
//         printf("Fejl ved åbning af filen\n");
//         return NULL;
//     };
    
//     fgets(tmpStringDeck, sizeof(tmpStringDeck), fp);
//     char* stringDeck = (char*) malloc(sizeof(tmpStringDeck));
//     strcpy(stringDeck, tmpStringDeck);
//     fclose(fp);
//     return stringDeck;
// }

// Card* initCard(){
//     Card *card = NULL;
//     card = (Card*)malloc(sizeof(Card));
//     card->isFlipped = false;
//     card->cardValue = ' ';
//     card->cardSuit = ' ';
//     card->previous = card;
//     card->next = card;

//     return card;
// }


//
// deck.c
//
// #define NUM_CARDS_ONE_DECK 52

// Card *createDeck(char* stringDeck) {
//     Card *deck = NULL;
//     Card *currentCard = NULL;
//     Card *previousCard = NULL;

//     // Init dummy card
//     deck = initCard();

//     previousCard = deck;

//     // Find length of the stringDeck
//     // It divids by 4 since each card in a file is representet by 3 chars and 1 whitespace
//     // Adds 1 to the count to compensate for the last cards missing whitespace
//     int numCards = strlen(stringDeck) / 4 +1;

//     // Checks if the file contains 52 cards, returns null and print error if it is more or less then
//     if(numCards != NUM_CARDS_ONE_DECK){
//         printf("Fejl i dækket: Dette er ikke et komplet sæt kort af 52\n");
//         return NULL;
//     }


//     // Creats each card in the order that is given in the file
//     for (int i = 0; i < numCards; i++){
//         currentCard = initCard();
//         currentCard->cardSuit = stringDeck[i*4];
//         currentCard->cardValue = stringDeck[i*4+2];
//         currentCard->previous = previousCard;

//         previousCard->next = currentCard;
//         previousCard = currentCard;
//     };

//     // Links first card (Dummy Card) to the last card
//     currentCard->next = deck;
//     deck->previous = currentCard;

//     return deck;
// }


// void printDeck(Card *deck) {
//     Card *currentCard = deck->next;
//     printf("Deck:\n");
//     while (true) {
//         printf("%c%c ", currentCard->cardSuit, currentCard->cardValue);
//         currentCard = currentCard->next;
//         if(currentCard->cardSuit == ' '){
//             break;
//         };
//     }
//     printf("\n\n");
// }


//
// LD command
//


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

// int randomNumber(int max){
//     // Sets a random seed for the Rand function
//     srand(time(NULL));
//     // Finds a random number between 0 and max
//     int randomInt = rand() % max;
//     //printf("RandomInt: %d\n", randomInt);
//     return randomInt;
// };

// int deckLength(Card* deck) {
//     int count = 0;
//     Card* current = deck;
//     while (true) {
//         count++;
//         current = current->next;
//         if(current == deck){
//             break;
//         }
//     }
//     return count-1;
// }

// int shuffleDeck(Card* deck, int split){

//     Card *pileOne = initCard();
//     Card *pileTwo = initCard();
//     Card* currentCard = deck->next;

//     //Divide the deck in to to piles based on split value
//     for(int i = 0; i < split; i++){
//         currentCard = currentCard->next;
//     };

//     pileOne->next = deck->next;
//     pileOne->previous = currentCard->previous;

//     pileTwo->next = currentCard;
//     pileTwo->previous = deck->previous;

//     pileOne->previous->next = pileOne;
//     pileTwo->previous->next = pileTwo;

//     // printDeck(pileOne);
//     // printDeck(pileTwo);

//     Card *deckTopCard = deck;
//     Card *pileOneCurrentCard = pileOne->next;
//     Card *pileTwoCurrentCard = pileTwo->next;
//     Card *pileOneNextCard;
//     Card *pileTwoNextCard;

//     // TODO: Comment
//     while(true){
//         if(pileOneCurrentCard->cardValue != ' ' && pileTwoCurrentCard->cardValue != ' '){
//             pileOneNextCard = pileOneCurrentCard->next;
//             pileTwoNextCard = pileTwoCurrentCard->next;

//             deckTopCard->next = pileOneCurrentCard;
//             pileOneCurrentCard->next = pileTwoCurrentCard;
//             pileTwoCurrentCard->next = deck;

//             pileOneCurrentCard->previous = deckTopCard;
//             pileTwoCurrentCard->previous = pileOneCurrentCard;
//             deck->previous = pileTwoCurrentCard;

//             deckTopCard = pileTwoCurrentCard;

//             pileOneCurrentCard = pileOneNextCard;
//             pileTwoCurrentCard = pileTwoNextCard;
//         } else if(pileOneCurrentCard->cardValue != ' '){
//             pileOneNextCard = pileOneCurrentCard->next;

//             deckTopCard->next = pileOneCurrentCard;
//             pileOneCurrentCard->previous = deckTopCard;

//             pileOneCurrentCard->next = deck;
//             deck->previous = pileOneCurrentCard;

//             deckTopCard = pileOneCurrentCard;

//             pileOneCurrentCard = pileOneNextCard;
//         } else if(pileTwoCurrentCard->cardValue != ' '){
//             pileTwoNextCard = pileTwoCurrentCard->next;

//             deckTopCard->next = pileTwoCurrentCard;
//             pileTwoCurrentCard->previous = deckTopCard;

//             pileTwoCurrentCard->next = deck;
//             deck->previous = pileTwoCurrentCard;

//             deckTopCard = pileTwoCurrentCard;

//             pileTwoCurrentCard = pileTwoNextCard;
//         } else {
//             break;
//         };
//     };

//     return 0;
// };

//
// SL command
//
// int SL(Card* deck, char* split){
//     int splitInt;
//     if(strcmp(split, "") == 0){
//         splitInt = randomNumber(53);
//     }else{
//         splitInt = stringToInt(split);
//         if(splitInt < 53 && 0 > splitInt){
//             printf("Fejl: Tallet er 0 eller negativ, eller større end mængden af kort i dækket");
//             return 1;
//         }
//     };
//     shuffleDeck(deck, splitInt);
//     return 0;
// }


//
// SR
//
// int SR(Card* deck){
//     shuffleDeckRandom(deck);
//     return 0;
// }

// int shuffleDeckRandom(Card* deck){
//     int deckSize = deckLength(deck);
//     Card *unshuffledDeck = initCard();
//     unshuffledDeck->next = deck->next;
//     unshuffledDeck->previous = deck->previous;

//     deck->next = deck;
//     deck->previous = deck;

//     Card *currentCard = unshuffledDeck->next;
//     Card *nextCard;
//     Card *cardOnIndex = deck->next;
//     int cardIndexPlacement;

//     for (int i=1; i <=deckSize; i++){
//         cardIndexPlacement = randomNumber(i)+1;
//         for (int j=1; j<=cardIndexPlacement; j++){
//             cardOnIndex = cardOnIndex->next;
//         };
//         nextCard = currentCard->next;
//         currentCard->next = cardOnIndex->next;
//         cardOnIndex->next = currentCard;
//         currentCard->previous = cardOnIndex;

//         currentCard = nextCard;

//     };
//     return 0;
// }

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
        if(currentCard->cardSuit==' '){
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


// int main() { 
//     Card *deck = LD(NULL);
//     SL(deck, "32");
//     //saveDeckToFile(deck);
//     printDeck(deck);
//     return 0;
// };