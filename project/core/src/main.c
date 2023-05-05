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

int main() {

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
        char input[101];
        fgets(input,sizeof(input),stdin);


            if (input[0] == 'L' && input[1] == 'D') { //LD command
                if (gameStarted) {
                    strcpy(commandLine.command, "LD");
                    strcpy(commandLine.message, "Command not available in the PLAY phase");

                } else {
                    if (input[2] == '\n') {
                        //No file specified
                        char* stringDeck = loadFile(NULL);
                        Deck = createDeck(stringDeck);
                        free(stringDeck);

                        printDeck(Deck);
                    } else {
                        //file specified

                    }
                    deckLoaded = true;

                }

                print_board(&gameBoard, false);
                printCommandLine(&commandLine);

            } else if (input[0] == 'S' && input[1] == 'W') { //SW command
                bool commandSuccessfull = false;

                if (gameStarted) {
                    strcpy(commandLine.command, "SW");
                    strcpy(commandLine.message, "Command not available in the PLAY phase");
                } else {
                    if (input[2] == '\n') {
                        if (deckLoaded == false) {
                            strcpy(commandLine.command, "SW");
                            strcpy(commandLine.message, "ERROR no deck");

                        } else {
                            strcpy(commandLine.command, "SW");
                            strcpy(commandLine.message, "ok");
                            commandSuccessfull = true;
                        }
                    } else {
                        strcpy(commandLine.command, " ");
                        strcpy(commandLine.message, "Incorect command");
                    }
                }
                printCommandLine(&commandLine);
                print_board(&gameBoard, commandSuccessfull);

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
                isRunning = false;

            } else if (input[0] == 'P') { //P command
                if (input[1] == '\n') {
                    if (gameStarted) {
                        strcpy(commandLine.command, "SW");
                        strcpy(commandLine.message, "Command not available in the PLAY phase");
                    } else {
                        if (!deckLoaded) {
                            strcpy(commandLine.command, "P");
                            strcpy(commandLine.message, "ERROR no deck");
                        } else {
                            gameStarted = true;
                            deal_cards(&gameBoard, Deck);
                            strcpy(commandLine.command, "P");
                            strcpy(commandLine.message, "OK");
                        }
                    }
                } else {
                    strcpy(commandLine.command, " ");
                    strcpy(commandLine.message, "Incorect command");
                }

                print_board(&gameBoard, false);
                printCommandLine(&commandLine);

            } else if (input[0] == 'Q') {
                if (input[1] == '\n') {
                    if (gameStarted) {
                        gameStarted = false;

                        //reload the deck
                    } else {
                        strcpy(commandLine.command, "Q");
                        strcpy(commandLine.message, "Command not available in the STARTUP phase");
                    }
                } else {
                    strcpy(commandLine.command, " ");
                    strcpy(commandLine.message, "Incorect command");
                }

                print_board(&gameBoard, false);
                printCommandLine(&commandLine);

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
                                    if (destination->cardValue == ' ' && fromColumn->previous->cardValue == '1' ) {  //CHANGE to A
                                        Card* toMove = pop_last_in_list(fromColumn);
                                        insert_next_in_list(destination->next, toMove);

                                        char msg[30];
                                        sprintf(msg,"C%c->F%c", input[1],input[5]);
                                        strcpy(commandLine.command, msg);
                                        strcpy(commandLine.message, "OK");

                                    } else if (destination->cardSuit == fromColumn->previous->cardSuit && ASCII_to_numeric((int)destination->cardValue) - ASCII_to_numeric((int)fromColumn->previous->cardValue) == -1 ) {

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
                                if (input[5] == '1'|| input[5] == '2' || input[5] == '3' || input[5] == '4' || input[5] == '5' || input[5] == '6' || input[5] == '7') {
                                    Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[5])-1]->previous;

                                    if (destination->cardValue == ' ' && fromColumn->previous->cardValue == 'K') {
                                        Card* toMove = pop_last_in_list(fromColumn);
                                        insert_next_in_list(destination->next, toMove);

                                        char msg[30];
                                        sprintf(msg,"C%c->C%c", input[1],input[5]);
                                        strcpy(commandLine.command, msg);
                                        strcpy(commandLine.message, "OK");

                                    } else if (destination->cardSuit != fromColumn->previous->cardSuit && ASCII_to_numeric((int)destination->cardValue) - ASCII_to_numeric((int)fromColumn->previous->cardValue) == 1 ) {

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
                            if (destination->cardValue == ' ' && toMove->cardValue == '1') { //change to A when cards are fixed
                                toMove = pop_last_in_list(toMove->next);
                                insert_next_in_list(destination->next, toMove);

                                char msg[30];
                                sprintf(msg,"F%c->C%c", toMove->cardValue, destination->cardValue);
                                strcpy(commandLine.command, msg);
                                strcpy(commandLine.message, "OK");
                            } else if (toMove->cardValue == ' ') {
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
             }

            print_board(&gameBoard, false);
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
        printf("LAST Command: %s \n", commandLine->command);
        printf("Message: %s \n", commandLine->message);
        printf("INPUT > ");
    }
}






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


