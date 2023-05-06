#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <stdio.h>

#define COMMAND_SIZE 101
#define MESSAGE_SIZE 101

typedef struct commandLine {
    char command[COMMAND_SIZE];
    char message[MESSAGE_SIZE];
}CommandLine;

extern void printCommandLine (CommandLine* commandLine);
void setCommandLine (CommandLine* commandLine, char msg[], char command[]);

#endif