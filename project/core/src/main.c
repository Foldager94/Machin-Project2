#include <stdio.h>
#include <string.h>
#include "board.h"
#include "card.h"
#include "commandLine.h"
#include "deck.h"
#include <stdbool.h>
#include <stdlib.h>
#include "test.h"
#include <time.h>


#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void printCommandLine(CommandLine*);


void clearScreen(){
    system("@cls||clear");
}

// Remember to free up the malloc after use
char* readParameter(char input[]){
    char* param = (char*)malloc(99);
    strcpy(param, input+3);
    return param;
}

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
        if (destination->cardValue == ' ' && toMove->cardValue == 'A') {
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

void moveSingleCard (Card* toMoveColumn, Card* destination) {
    Card* newLast = toMoveColumn->previous->previous;
    newLast->isFlipped = true;

    Card* toMove = pop_last_in_list(toMoveColumn);
    insert_next_in_list(destination->next, toMove);
}

void moveListOfCards (Card* first, Card* fromDummy, Card* toDummy) {
    Card* newLast = first->previous;
    newLast->isFlipped = true;

    Card* last = fromDummy->previous;

    remove_list_in_list(fromDummy, first);
    insert_list_in_list(toDummy,first,last);
}

bool checkWin (Board* gameboard) {

    bool isWon = true;

    for (int i = 0; i < 7; i++) {
        if (gameboard->columns[i]->previous->cardValue != ' ') {
            isWon = false;
            break;
        }
    }

    return isWon;
}

int main() {
    runTests();
    clearScreen();

    char NOT_AVAILABLE[] = "Command not available in the PLAY phase";
    char NO_DECK[] = "ERROR: No deck";
    char ERROR[] = "ERROR: Unknown command";
    char OK[] = "OK";
    char NO_FILE[] = "File not found";

    Board gameBoard;
    Card* deck;
    Card* deckCopy;
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

    while (isRunning) {
        bool showAll = false;
        char input[101];
        fgets(input,sizeof(input),stdin);

        char command[30];


            //Determening the input
            if (input[0] == 'L' && input[1] == 'D') { //LD command
                if (gameStarted) {
                    setCommandLine(&commandLine, NOT_AVAILABLE, input);
                } else {
                    char* parameter = NULL;

                    if (input[2] != '\n') {
                        parameter = readParameter(input);
                    }
                    deck = load_deck(parameter);
                    if (deck != NULL) {
                        deckCopy = init_list();
                        make_copy(deck, deckCopy);
                        place_deck(&gameBoard, deckCopy);
                        deckLoaded = true;

                        setCommandLine(&commandLine, OK, input);
                    } else {
                        setCommandLine(&commandLine, NO_FILE, input);
                    }
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
                            for (int i = 0; i < COL_COUNT; i++) {
                                clear_list(gameBoard.columns[i]);
                            }
                            deal_cards(&gameBoard, deck);
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

                                                if (checkWin(&gameBoard)) {
                                                    setCommandLine(&commandLine, "You have won!", input);
                                                } else {
                                                    setCommandLine(&commandLine,OK,input);
                                            }
                                        }
                                } else if (input[7] == 'C') {
                                    if (validateColumn(input[8])) {
                                        Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[8])-1]->previous;

                                        //Validate move
                                        if (validateMoveToColumn(toMove, destination)) {

                                            moveListOfCards(toMove,fromColumn,destination->next);

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

                                        if (checkWin(&gameBoard)) {
                                            setCommandLine(&commandLine, "You have won!", input);
                                        } else {
                                            setCommandLine(&commandLine,OK,input);
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

            clearScreen();
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

