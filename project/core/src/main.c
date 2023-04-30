#include <stdio.h>
#include <malloc/_malloc.h>
#include <strings.h>
#include "board.h"
#include "card.h"
#include "commandLine.h"

#define MIN_LINE_PRINT 8
#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void printBoard(Board*, bool showAll);
void printCommandLine(CommandLine*);

int main() {

    Board gameBoard;
    CommandLine commandLine;

    //Initialize dummy elements
    for (int i = 0; i < COL_COUNT; i++) {
        Card *dummy;
        dummy = (Card*)malloc(sizeof(Card));

        dummy->cardValue = ' ';
        dummy->previous = dummy;
        dummy->next = dummy;
        gameBoard.columns[i] = dummy;
    }

    for (int i = 0; i < FOUNDATION_COUNT; i++) {
        Card *dummy;
        dummy = (Card*)malloc(sizeof(Card));

        dummy->cardValue = ' ';
        dummy->previous = dummy;
        dummy->next = dummy;
        gameBoard.foundations[i] = dummy;
    }

    //Initialize commands
    commandLine.command[0] = ' ';
    commandLine.message[0] = ' ';


    printBoard(&gameBoard, false);
    printCommandLine(&commandLine);

    bool isRunning = true;
    bool gameStarted = false;
    bool deckLoaded = false;
    Card* cards[52];

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
                    } else {
                        //file specified
                    }
                    deckLoaded = true;

                }

                //Print stuff

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
                printBoard(&gameBoard, commandSuccessfull);

            } else if (input[0] == 'S' && input[1] == 'I') { //SI command
                if (input[2] == '\n') {
                    //No split specified
                } else {
                    //split specified
                }

            } else if (input[0] == 'S' && input[1] == 'R') { //SR command


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
                            dealCards(&gameBoard, cards);
                            strcpy(commandLine.command, "P");
                            strcpy(commandLine.message, "OK");
                        }
                    }
                } else {
                    strcpy(commandLine.command, " ");
                    strcpy(commandLine.message, "Incorect command");
                }

                printBoard(&gameBoard, false);
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

                printBoard(&gameBoard, false);
                printCommandLine(&commandLine);

            } else if (input[0] == 'C' ) { //Move command




            } else if (input[0] == 'F') { //Move from faundation
                if (input[1] == '1' || input[1] == '2' || input[1] == '3' || input[1] == '4') { //The FROM is recognized
                    if (input[2] == '-' && input[3] == '>') { //Midle is recognized
                        if (input[4] == 'C' && input[5] == '1' || input[5] == '2' || input[5] == '3' || input[5] == '4' || input[5] == '5' || input[5] == '6' || input[5] == '7') { //To is recognized
                            //Validate the move
                            //if valid move the card
                            //Set message and command
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

                printBoard(&gameBoard, false);
                printCommandLine(&commandLine);

            } else { //unknown command
                strcpy(commandLine.command, " ");
                strcpy(commandLine.message, "Incorect command");
                printBoard(&gameBoard, false);
                printCommandLine(&commandLine);
            }
        }



    //Will be deleted in time

    //Card* cards[52];
    for (int i = 0; i < 52; i++) {
        Card *t;
        t = (Card*) malloc(sizeof(Card));
        t->cardValue = '3';
        t->cardSuit = 'H';

        cards[i] = t;
    }

    dealCards(&gameBoard, cards);


    //Card *t;
    //t = (Card*) malloc(sizeof(Card));
    //t->cardValue = '3';
    //t->cardSuit = 'H';

    //insertNext(gameBoard.columns[0], t);



    //printBoard(gameBoard, false);

    return 0;

}







//Print the board with the current cards
void printBoard(Board* gameBoard, bool showAll) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\n\n");

    int emptyCounter = 0;
    bool emptyColumns[7] = { false, false, false, false, false, false, false};
    int counter = 0;
    int foundationCounter = 0;

    // Pointers to each column card
    Card* cards[COL_COUNT];
    for (int i = 0; i < COL_COUNT; i++) {
        cards[i] = gameBoard->columns[i]->next;
    }

    while (counter < MIN_LINE_PRINT || emptyCounter < COL_COUNT) {

        // Print from each column
        for (int i = 0; i < COL_COUNT; i++) {
            Card* current = cards[i];
            if (current->cardValue == ' ') {
                printf(" ");
                if (!emptyColumns[i]) {
                    emptyColumns[i] = true;
                    emptyCounter++;
                }
            } else {
                if (!current->isFlipped && !showAll) {
                    printf("[]");
                } else {
                    printf("%c%c", current->cardValue, current->cardSuit);
                }
                cards[i] = current->next;
            }
            printf("\t");
        }

        // Print the foundations on the right side
        if ((counter & 1) && (counter < (FOUNDATION_COUNT * 2))) {
            Card* fCard = gameBoard->foundations[foundationCounter]->previous;
            if (fCard->cardValue != ' ') {
                printf("\t%c%c\tF%i", fCard->cardValue, fCard->cardSuit, foundationCounter + 1);
            } else {
                printf("\t[]\tF%i", foundationCounter + 1);
            }

            foundationCounter++;
        }

        printf("\n");
        counter++;
    }
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