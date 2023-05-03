#include <stdio.h>
#include <strings.h>
#include "board.h"
#include "card.h"
#include "commandLine.h"

#define COL_COUNT 7
#define FOUNDATION_COUNT 4

void printCommandLine(CommandLine*);

int main() {

    Board gameBoard;
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
                print_board(&gameBoard, commandSuccessfull);

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
                            deal_cards(&gameBoard, deck);
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

                print_board(&gameBoard, false);
                printCommandLine(&commandLine);

            } else { //unknown command
                strcpy(commandLine.command, " ");
                strcpy(commandLine.message, "Incorect command");
                print_board(&gameBoard, false);
                printCommandLine(&commandLine);
            }
        }

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