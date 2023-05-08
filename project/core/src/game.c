#include <stdio.h>
#include "board.h"
#include "card.h"
#include "commandLine.h"
#include "deck.h"
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
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

void run_game() {
    char NOT_AVAILABLE[] = "Command not available in the PLAY phase";
    char NO_DECK[] = "ERROR: No deck";
    char ERROR[] = "ERROR: Unknown command";
    char INVALID[] = "ERROR: Invalid move";
    char OK[] = "OK";
    char NO_FILE[] = "ERROR: File not found";
    char INVALID_FILE[] = "ERROR: File is invalid. Error on line   ";
    char WINNER[] = "You win!!!";
    char SPLIT_ERROR[] = "ERROR: Split must be between 1 - 52";
    char SAVE_FILE_ERROR[]= "ERROR: Could not save the deck";

    Board gameBoard;
    Card* deck = init_list();
    Card* deckCopy = init_list();
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


        //Determining the input
        if (toupper(input[0]) == 'L' && toupper(input[1]) == 'D') { //LD command
            if (gameStarted) {
                setCommandLine(&commandLine, NOT_AVAILABLE, input);
            } else {
                char* parameter = NULL;

                if (input[2] != '\n') {
                    parameter = readParameter(input);
                }
                clear_list(deck);
                int loadResponse = load_deck(parameter, deck);
                if (loadResponse == 0) { // No error
                    // Clear copy and board
                    clear_list(deckCopy);
                    for (int i = 0; i < COL_COUNT; i++) {
                        clear_list(gameBoard.columns[i]);
                        if (i < FOUNDATION_COUNT) {
                            clear_list(gameBoard.foundations[i]);
                        }
                    }

                    // Make copy and place it
                    make_copy(deck, deckCopy);
                    place_deck(&gameBoard, deckCopy);

                    deckLoaded = true;

                    setCommandLine(&commandLine, OK, input);
                } else if (loadResponse == -1) { // File not found
                    setCommandLine(&commandLine, NO_FILE, input);
                } else { // Line error
                    if (loadResponse > 9) {
                        int firstDigit = loadResponse / 10;
                        int secondDigit = loadResponse % 10;
                        INVALID_FILE[38] = (char)(firstDigit + '0');
                        INVALID_FILE[39] = (char)(secondDigit + '0');
                    } else {
                        INVALID_FILE[38] = (char)(loadResponse + '0');
                    }

                    setCommandLine(&commandLine, INVALID_FILE, input);
                }
            }



        } else if (toupper(input[0]) == 'S' && toupper(input[1]) == 'W') { //SW command

            if (gameStarted) {
                setCommandLine(&commandLine, NOT_AVAILABLE, input);
            } else {
                if (input[2] == '\n') {
                    if (deckLoaded == false) {
                        setCommandLine(&commandLine, NO_DECK, input);
                    } else {
                        setCommandLine(&commandLine, OK, input);
                        // Clear copy and board
                        clear_list(deckCopy);
                        for (int i = 0; i < COL_COUNT; i++) {
                            clear_list(gameBoard.columns[i]);
                            if (i < FOUNDATION_COUNT) {
                                clear_list(gameBoard.foundations[i]);
                            }
                        }

                        // Make copy and place it
                        make_copy(deck, deckCopy);
                        place_deck(&gameBoard, deckCopy);
                        showAll = true;
                    }
                } else {
                    setCommandLine(&commandLine, ERROR, input);
                }
            }



        } else if (toupper(input[0]) == 'S' && toupper(input[1]) == 'I') { //SI command
            int splitInt;
            if (input[2] == '\n') {
                //No split specified
                splitInt = randomNumber(53);
                shuffleDeck(deck, splitInt);
                setCommandLine(&commandLine,OK,input);
            } else {
                //split specified
                if(input[5] == '\n'){
                    splitInt = ASCII_to_numeric(input[3])*10+ASCII_to_numeric(input[4]);
                    printf("%d",splitInt);
                        if(0 < splitInt && splitInt < 53){
                            shuffleDeck(deck, splitInt);
                            setCommandLine(&commandLine,OK,input);
                        }else{
                            setCommandLine(&commandLine,SPLIT_ERROR,input);
                        }
                }else if(input[4] == '\n'){
                    splitInt = ASCII_to_numeric(input[3]);
                    printf("%d",splitInt);
                    if(0 < splitInt && splitInt < 9){
                        shuffleDeck(deck, splitInt);
                        setCommandLine(&commandLine,OK,input);
                    }else{
                        setCommandLine(&commandLine,SPLIT_ERROR,input);
                    }
                }else {
                    setCommandLine(&commandLine,SPLIT_ERROR,input);
                }


            }



        } else if (toupper(input[0]) == 'S' && toupper(input[1]) == 'R') { //SR command
            if (!gameStarted) {
                shuffleDeckRandom(deck);
                setCommandLine(&commandLine,OK,input);
            } else {
                setCommandLine(&commandLine,NOT_AVAILABLE,input);
            }



        } else if (toupper(input[0]) == 'S' && toupper(input[1]) == 'D') { //SD command
            if (gameStarted) {
                setCommandLine(&commandLine, NOT_AVAILABLE, input);
            } else {
                char* parameter = NULL;

                if (input[2] != '\n') {
                    parameter = readParameter(input);
                }
                int loadResponse = saveDeckToFile(deck, parameter);
                printf("%d", loadResponse);
                if (loadResponse == 0) { // No error
                    setCommandLine(&commandLine,OK,input);
                }else{
                    setCommandLine(&commandLine,SAVE_FILE_ERROR,input);
                }
            }


        } else if (toupper(input[0]) == 'Q' && toupper(input[1]) == 'Q') { //QQ command
            isRunning = false;
            /*if (!gameStarted) {
                isRunning = false;
            } else {
                setCommandLine(&commandLine,NOT_AVAILABLE,input);
            }*/
        } else if (toupper(input[0]) == 'P') { //P command
            if (input[1] == '\n') {
                if (gameStarted) {
                    setCommandLine(&commandLine, NOT_AVAILABLE, input);
                } else {
                    if (!deckLoaded) {
                        setCommandLine(&commandLine, NO_DECK, input);
                    } else {
                        //Deal cards and start game
                        gameStarted = true;

                        // Clear copy and board
                        clear_list(deckCopy);
                        for (int i = 0; i < COL_COUNT; i++) {
                            clear_list(gameBoard.columns[i]);
                            if (i < FOUNDATION_COUNT) {
                                clear_list(gameBoard.foundations[i]);
                            }
                        }

                        // Make copy and deal cards
                        make_copy(deck, deckCopy);
                        deal_cards(&gameBoard, deckCopy);
                        setCommandLine(&commandLine, OK, input);
                    }
                }
            } else {
                setCommandLine(&commandLine, ERROR, input);
            }



        } else if (toupper(input[0]) == 'Q') {
            if (input[1] == '\n') {
                if (gameStarted) {
                    gameStarted = false;

                    // Clear copy and board
                    clear_list(deckCopy);
                    for (int i = 0; i < COL_COUNT; i++) {
                        clear_list(gameBoard.columns[i]);
                        if (i < FOUNDATION_COUNT) {
                            clear_list(gameBoard.foundations[i]);
                        }
                    }

                    // Make copy and place it
                    make_copy(deck, deckCopy);
                    place_deck(&gameBoard, deckCopy);

                    setCommandLine(&commandLine, OK, input);
                } else {
                    setCommandLine(&commandLine, NOT_AVAILABLE, input);
                }
            } else {
                setCommandLine(&commandLine, ERROR, input);
            }



        } else if (toupper(input[0]) == 'C' ) { //Move command
            //Set defealt command and message
            setCommandLine(&commandLine, ERROR, input);

            if (validateColumn(input[1])) {
                Card* fromColumn = gameBoard.columns[ASCII_to_numeric((int) input[1])-1];         //Save the column to move from

                if (input[2] == ':'){
                    Card* toMove = find_card(fromColumn, toupper(input[3]), input[4]);

                    if (toMove->cardValue != ' ') {
                        if (input[5] == '-' && input[6] == '>') {
                            if (toupper(input[7]) == 'F') {
                                if (validateFoundation(input[8])) {
                                    Card* destination = gameBoard.foundations[ASCII_to_numeric((int) input[8])-1]->previous;

                                    if (validateMoveToFoundation(toMove, destination)) {
                                        moveSingleCard(fromColumn,destination);

                                        if (checkWin(&gameBoard)) {
                                            setCommandLine(&commandLine, WINNER, input);
                                        } else {
                                            setCommandLine(&commandLine, OK, input);
                                        }
                                    } else {
                                        setCommandLine(&commandLine, INVALID, input);
                                    }
                                }
                            } else if (toupper(input[7]) == 'C') {
                                if (validateColumn(input[8])) {
                                    Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[8])-1]->previous;

                                    //Validate move
                                    if (validateMoveToColumn(toMove, destination)) {

                                        moveListOfCards(toMove,fromColumn,destination->next);

                                        setCommandLine(&commandLine, OK, input);
                                    } else {
                                        setCommandLine(&commandLine, INVALID, input);
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (input[2] == '-' && input[3] == '>') {
                        if (toupper(input[4]) == 'F') {
                            if (validateFoundation(input[5])) {
                                Card* destination = gameBoard.foundations[ASCII_to_numeric((int) input[5])-1]->previous;

                                if (validateMoveToFoundation(fromColumn->previous, destination)) {
                                    moveSingleCard(fromColumn,destination);

                                    if (checkWin(&gameBoard)) {
                                        setCommandLine(&commandLine, WINNER, input);
                                    } else {
                                        setCommandLine(&commandLine, OK, input);
                                    }
                                } else {
                                    setCommandLine(&commandLine, INVALID, input);
                                }
                            }
                        } else if (toupper(input[4]) == 'C') {
                            if (validateColumn(input[5])) {
                                Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[5])-1]->previous;

                                if (validateMoveToColumn(fromColumn->previous, destination)) {
                                    moveSingleCard(fromColumn,destination);
                                    setCommandLine(&commandLine, OK, input);
                                } else {
                                    setCommandLine(&commandLine, INVALID, input);
                                }
                            }
                        }
                    }
                }
            }




        } else if (toupper(input[0]) == 'F') { //Move from faundation
            //Set defealt command and message
            setCommandLine(&commandLine, ERROR, input);

            if (validateFoundation(input[1])) {
                Card*  fromColumn = gameBoard.foundations[ASCII_to_numeric((int) input[1])-1];

                if (input[2] == '-' && input[3] == '>') {
                    if (toupper(input[4]) == 'C' && validateColumn(input[5])) {
                        Card* toMove = gameBoard.foundations[ASCII_to_numeric((int) input[1])-1]->previous;
                        Card* destination = gameBoard.columns[ASCII_to_numeric((int) input[5])-1]->previous;

                        //Check if piles are empty
                        if (validateMoveToColumn(toMove, destination)) {
                            moveSingleCard(fromColumn, destination);

                            setCommandLine(&commandLine, OK, input);
                        }
                    }
                }
            }
        } else {
            setCommandLine(&commandLine, ERROR, input);
        }

        //clearScreen();
        print_board(&gameBoard, showAll);
        printCommandLine(&commandLine);
    }
}