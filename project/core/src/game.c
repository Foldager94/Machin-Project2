#include <stdio.h>
#include "../include/board.h"
#include "../include/card.h"
#include "../include/commandLine.h"
#include "../include/deck.h"
#include "../include/gameState.h"
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
        } else if (destination->cardSuit == toMove->cardSuit && asciiToNumeric((int) destination->cardValue) - asciiToNumeric((int) toMove->cardValue) == -1 ) {
            return true;
        } else return false;
    } else return false;

}

bool validateMoveToColumn (Card* toMove, Card* destination) {
    if (destination->cardValue == ' ' && toMove->cardValue == 'K') {
        return true;
    } else if (destination->cardSuit != toMove->cardSuit && asciiToNumeric((int) destination->cardValue) - asciiToNumeric((int) toMove->cardValue) == 1 ) {
        return true;
    } else return false;
}

void moveSingleCard (Card* toMoveColumn, Card* destination) {
    Card* newLast = toMoveColumn->previous->previous;
    newLast->isFlipped = true;

    Card* toMove = popLastInList(toMoveColumn);
    insertNextInList(destination->next, toMove);
}

void moveListOfCards (Card* first, Card* fromDummy, Card* toDummy) {
    Card* newLast = first->previous;
    newLast->isFlipped = true;

    Card* last = fromDummy->previous;

    removeListInList(fromDummy, first);
    insertListInList(toDummy, first, last);
}

bool checkWin (Board* board) {

    bool isWon = true;

    for (int i = 0; i < COL_COUNT; i++) {
        if (board->columns[i]->previous->cardValue != ' ') {
            isWon = false;
            break;
        }
    }

    return isWon;
}

Card* createKing (char suit) {
    Card *newCard = (Card *) malloc(sizeof(Card));
    newCard->isFlipped = true;
    newCard->cardSuit = suit;
    newCard->cardValue = 'K';

    return newCard;
}

void autoComplete (Board* board) {
    for (int i = 0; i < COL_COUNT; i++) {
        clearList(board->columns[i]);
    }

    char suits[] = "SDHC";
    char suitsUsed[] = "    ";

    for (int i = 0; i < FOUNDATION_COUNT; i++) {
        Card *current = board->foundations[i]->previous;

        if (current->cardSuit != ' ') {

            char suit = current->cardSuit;

            Card* newCard = createKing(suit);
            insertNextInList(board->foundations[i], newCard);

            suitsUsed[i] = suit;

            for (int j = 0; j < FOUNDATION_COUNT; j++) {
                if (suits[j] == suit) {
                    suits[j] = ' ';
                }
            }
        }
    }

    for (int i = 0; i < FOUNDATION_COUNT; i++) {
        if (suitsUsed[i] == ' ') {
            for (int j = 0; j < FOUNDATION_COUNT; j++) {
                if (suits[j] != ' ') {
                    Card* newCard = createKing(suits[j]);
                    insertNextInList(board->foundations[i], newCard);
                    suits[j] = ' ';
                    break;
                }
            }
        }
    }
}



void runGame() {
    char NOT_AVAILABLE[] = "Command not available in the PLAY phase";
    char NOT_AVAILABLE_STARTUP[] = "Command not available in the STARTUP phase";
    char NO_DECK[] = "ERROR: No deck";
    char ERROR[] = "ERROR: Unknown command";
    char INVALID[] = "ERROR: Invalid move";
    char OK[] = "OK";
    char NO_FILE[] = "ERROR: File not found";
    char INVALID_FILE[] = "ERROR: File is invalid. Error on line   ";
    char WINNER[] = "You win!!!";
    char SPLIT_ERROR[] = "ERROR: Split must be between 1 - 52";
    char SAVE_FILE_ERROR[]= "ERROR: Could not save the deck";
    char UNDO_INVALID[]= "Undo not available";
    char REDO_INVALID[]= "Undo not available";

    Board gameBoard;
    Card* deck = initList();
    Card* deckCopy = initList();
    CommandLine commandLine;
    GameState* gameState = initGameState();
    int gameStateCounter = 0;

    gameState->next = gameState;
    gameState->previous = gameState;

    //Initialize dummy elements
    for (int i = 0; i < COL_COUNT; i++) {
        gameBoard.columns[i] = initList();
    }

    for (int i = 0; i < FOUNDATION_COUNT; i++) {
        gameBoard.foundations[i] = initList();
    }

    //Initialize commands
    commandLine.command[0] = ' ';
    commandLine.message[0] = ' ';

    printBoard(&gameBoard, false);
    printCommandLine(&commandLine);

    bool isRunning = true;
    bool gameStarted = false;
    bool deckLoaded = false;

    while (isRunning) {
        bool showAll = false;
        char input[101];
        fgets(input,sizeof(input),stdin);

        //Determining the input
        if (toupper(input[0]) == 'L' && toupper(input[1]) == 'D') { //LD command
            if (gameStarted) {
                setCommandLine(&commandLine, NOT_AVAILABLE, input);
            } else {
                char* parameter = NULL;

                if (input[2] != '\n') {
                    parameter = readParameter(input);
                }
                clearList(deck);
                int loadResponse = loadDeck(parameter, deck);
                if (loadResponse == 0) { // No error
                    // Clear copy and board
                    clearList(deckCopy);
                    for (int i = 0; i < COL_COUNT; i++) {
                        clearList(gameBoard.columns[i]);
                        if (i < FOUNDATION_COUNT) {
                            clearList(gameBoard.foundations[i]);
                        }
                    }

                    // Make copy and place it
                    makeCopy(deck, deckCopy);
                    placeDeck(&gameBoard, deckCopy);

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
                        INVALID_FILE[39] = ' ';
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
                        clearList(deckCopy);
                        for (int i = 0; i < COL_COUNT; i++) {
                            clearList(gameBoard.columns[i]);
                            if (i < FOUNDATION_COUNT) {
                                clearList(gameBoard.foundations[i]);
                            }
                        }

                        // Make copy and place it
                        makeCopy(deck, deckCopy);
                        placeDeck(&gameBoard, deckCopy);
                        showAll = true;
                    }
                } else {
                    setCommandLine(&commandLine, ERROR, input);
                }
            }
        }else if (toupper(input[0]) == 'S' && toupper(input[1]) == 'I') { //SI command
            int splitInt;
            if (input[2] == '\n') {
                //No split specified
                splitInt = randomNumber(53);
                shuffleDeck(deck, splitInt);
                setCommandLine(&commandLine,OK,input);
            } else {
                //split specified
                if(input[5] == '\n'){
                    splitInt = asciiToNumeric(input[3])*10+asciiToNumeric(input[4]);
                    printf("%d",splitInt);
                        if(0 < splitInt && splitInt < 53){
                            shuffleDeck(deck, splitInt);
                            setCommandLine(&commandLine,OK,input);
                        }else{
                            setCommandLine(&commandLine,SPLIT_ERROR,input);
                        }
                }else if(input[4] == '\n'){
                    splitInt = asciiToNumeric(input[3]);
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
        }else if (toupper(input[0]) == 'S' && toupper(input[1]) == 'R') { //SR command
            if (!gameStarted) {
                shuffleDeckRandom(deck);
                setCommandLine(&commandLine,OK,input);
            } else {
                setCommandLine(&commandLine,NOT_AVAILABLE,input);
            }
        }else if (toupper(input[0]) == 'S' && toupper(input[1]) == 'D') { //SD command
            if (gameStarted) {
                setCommandLine(&commandLine, NOT_AVAILABLE, input);
            } else {
                char* parameter = NULL;

                if (input[2] != '\n') {
                    parameter = readParameter(input);
                }
                int loadResponse = saveDeckToFile(deck, parameter);
                if (loadResponse == 0) { // No error
                    setCommandLine(&commandLine,OK,input);
                }else{
                    setCommandLine(&commandLine,SAVE_FILE_ERROR,input);
                }
            }
        }else if (toupper(input[0]) == 'Q' && toupper(input[1]) == 'Q') { //QQ command
            if (!gameStarted) {
                isRunning = false;
            } else {
                setCommandLine(&commandLine,NOT_AVAILABLE,input);
        }
        }else if (toupper(input[0]) == 'P') { //P command
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
                        clearList(deckCopy);
                        for (int i = 0; i < COL_COUNT; i++) {
                            clearList(gameBoard.columns[i]);
                            if (i < FOUNDATION_COUNT) {
                                clearList(gameBoard.foundations[i]);
                            }
                        }

                        // Make copy and deal cards
                        makeCopy(deck, deckCopy);
                        dealCards(&gameBoard, deckCopy);
                        Board* lolBoard = makeBoardCopy(&gameBoard);
                        saveGameState(lolBoard, gameState);
                        setCommandLine(&commandLine, OK, input);
                    }
                }
            } else {
                setCommandLine(&commandLine, ERROR, input);
            }
        }else if (toupper(input[0]) == 'Q') {
            if (input[1] == '\n') {
                if (gameStarted) {
                    gameStarted = false;

                    // Clear copy and board
                    clearList(deckCopy);
                    for (int i = 0; i < COL_COUNT; i++) {
                        clearList(gameBoard.columns[i]);
                        if (i < FOUNDATION_COUNT) {
                            clearList(gameBoard.foundations[i]);
                        }
                    }

                    // Make copy and place it
                    makeCopy(deck, deckCopy);
                    placeDeck(&gameBoard, deckCopy);

                    setCommandLine(&commandLine, OK, input);
                } else {
                    setCommandLine(&commandLine, NOT_AVAILABLE, input);
                }
            } else {
                setCommandLine(&commandLine, ERROR, input);
            }



        }else if (toupper(input[0]) == 'C' ) { //Move command

            if (!gameStarted) {
                setCommandLine(&commandLine, NOT_AVAILABLE_STARTUP, input);
            } else {
                setCommandLine(&commandLine, ERROR, input);

                if (validateColumn(input[1])) {
                    Card *fromColumn = gameBoard.columns[asciiToNumeric((int) input[1]) -
                                                         1];         //Save the column to move from

                    if (input[2] == ':') {
                        Card *toMove = findCard(fromColumn, toupper(input[3]), toupper(input[4]));

                        if (toMove->cardValue != ' ') {
                            if (input[5] == '-' && input[6] == '>') {
                                if (toupper(input[7]) == 'F') {
                                    if (validateFoundation(input[8])) {
                                        Card *destination = gameBoard.foundations[asciiToNumeric((int) input[8]) -
                                                                                  1]->previous;

                                        if (validateMoveToFoundation(toMove, destination)) {
                                            moveSingleCard(fromColumn, destination);
                                            if(gameStateCounter != 0){
                                                removeGameState(gameState, gameStateCounter);
                                                gameStateCounter = 0;
                                            }
                                            Board* lolBoard = makeBoardCopy(&gameBoard);
                                            saveGameState(lolBoard, gameState);
                                            if (checkWin(&gameBoard)) {
                                                setCommandLine(&commandLine, WINNER, input);
                                                gameStarted = false;
                                            } else {
                                                setCommandLine(&commandLine, OK, input);
                                            }
                                        } else {
                                            setCommandLine(&commandLine, INVALID, input);
                                        }
                                    }
                                } else if (toupper(input[7]) == 'C') {
                                    if (validateColumn(input[8])) {
                                        Card *destination = gameBoard.columns[asciiToNumeric((int) input[8]) - 1]->previous;

                                        //Validate move
                                        if (validateMoveToColumn(toMove, destination)) {

                                            moveListOfCards(toMove, fromColumn, destination->next);
                                            if(gameStateCounter != 0){
                                                removeGameState(gameState, gameStateCounter);
                                                gameStateCounter = 0;
                                            }
                                            Board* lolBoard = makeBoardCopy(&gameBoard);
                                            saveGameState(lolBoard, gameState);
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
                                    Card *destination = gameBoard.foundations[asciiToNumeric((int) input[5]) - 1]->previous;

                                    if (validateMoveToFoundation(fromColumn->previous, destination)) {
                                        moveSingleCard(fromColumn, destination);
                                        if(gameStateCounter != 0){
                                            removeGameState(gameState, gameStateCounter);
                                            gameStateCounter = 0;
                                        }
                                        Board* lolBoard = makeBoardCopy(&gameBoard);
                                        saveGameState(lolBoard, gameState);
                                        if (checkWin(&gameBoard)) {
                                            setCommandLine(&commandLine, WINNER, input);
                                            gameStarted = false;
                                        } else {
                                            setCommandLine(&commandLine, OK, input);
                                        }
                                    } else {
                                        setCommandLine(&commandLine, INVALID, input);
                                    }
                                }
                            } else if (toupper(input[4]) == 'C') {
                                if (validateColumn(input[5])) {
                                    Card *destination = gameBoard.columns[asciiToNumeric((int) input[5]) - 1]->previous;

                                    if (validateMoveToColumn(fromColumn->previous, destination)) {
                                        moveSingleCard(fromColumn, destination);
                                        if(gameStateCounter != 0){
                                            removeGameState(gameState, gameStateCounter);
                                            gameStateCounter = 0;
                                        }
                                        Board* lolBoard = makeBoardCopy(&gameBoard);
                                        saveGameState(lolBoard, gameState);
                                        setCommandLine(&commandLine, OK, input);
                                    } else {
                                        setCommandLine(&commandLine, INVALID, input);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }else if (toupper(input[0]) == 'F') { //Move from foundation
            if (!gameStarted) {
                setCommandLine(&commandLine, NOT_AVAILABLE_STARTUP, input);
            } else {
                //Set default command and message
                setCommandLine(&commandLine, ERROR, input);

                if (validateFoundation(input[1])) {
                    Card *fromColumn = gameBoard.foundations[asciiToNumeric((int) input[1]) - 1];

                    if (input[2] == '-' && input[3] == '>') {
                        if (input[4] == 'C' && validateColumn(input[5])) {
                            Card *toMove = gameBoard.foundations[asciiToNumeric((int) input[1]) - 1]->previous;
                            Card *destination = gameBoard.columns[asciiToNumeric((int) input[5]) - 1]->previous;

                            //Check if piles are empty
                            if (validateMoveToColumn(toMove, destination)) {
                                moveSingleCard(fromColumn, destination);
                                if(gameStateCounter != 0){
                                    removeGameState(gameState, gameStateCounter);
                                    gameStateCounter = 0;
                                }
                                Board* lolBoard = makeBoardCopy(&gameBoard);
                                saveGameState(lolBoard, gameState);

                                setCommandLine(&commandLine, OK, input);
                            }
                        }
                    }
                }
            }
        }else if (toupper(input[0]) == 'A' && toupper(input[1]) == 'U' && toupper(input[2]) == 'T' && toupper(input[3]) == 'O') {
            bool notAbleToComplete = false;

            for (int i = 0; i < COL_COUNT; i++) {
                Card* current = gameBoard.columns[i]->next;

                if (!current->isFlipped) {
                    notAbleToComplete = true;
                    break;
                }


                while (current->next->cardValue != ' ') {
                    int currentValue = asciiToNumeric(current->cardValue);
                    int nextValue = asciiToNumeric(current->next->cardValue);

                    if (currentValue - nextValue != 1) {
                        notAbleToComplete = true;
                    }

                    current = current->next;
                }
            }

            if (notAbleToComplete) {
                setCommandLine(&commandLine, INVALID, input);
            } else {
                setCommandLine(&commandLine, WINNER, input);
                autoComplete(&gameBoard);
                gameStarted = !checkWin(&gameBoard);
            }
        }else if (toupper(input[0]) == 'U' && toupper(input[1]) == 'N' && toupper(input[2]) == 'D' && toupper(input[3]) == 'O') {
                gameStateCounter++;
                if(isAtBeginig(gameState, gameStateCounter) == true) {
                    changeGameState(&gameBoard, gameState, gameStateCounter);
                    setCommandLine(&commandLine, OK, input);
                }else{
                    setCommandLine(&commandLine, ERROR, input);
                    gameStateCounter--;
                }


        }else if (toupper(input[0]) == 'R' && toupper(input[1]) == 'E' && toupper(input[2]) == 'D' && toupper(input[3]) == 'O') {
            if(gameStateCounter >0) {
                gameStateCounter--;
                changeGameState(&gameBoard, gameState, gameStateCounter);
                setCommandLine(&commandLine, OK, input);
            }
        } else {
            setCommandLine(&commandLine, ERROR, input);
        }

        clearScreen();
        printBoard(&gameBoard, showAll);
        printCommandLine(&commandLine);
    }
}