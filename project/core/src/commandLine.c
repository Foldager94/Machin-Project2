//
// Created by Sandie on 06-05-2023.
//
#include <string.h>

#include "commandLine.h"


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

void setCommandLine (CommandLine* commandLine, char msg[], char command[]) {
    strcpy(commandLine->message, msg);
    strcpy(commandLine->command, command);
}