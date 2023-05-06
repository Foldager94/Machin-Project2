//
// Created by Sandie on 06-05-2023.
//

#ifndef MACHIN_PROJECT2_GAME_H
#define MACHIN_PROJECT2_GAME_H

#include <stdbool.h>
#include "card.h"
#include "board.h"

extern void clearScreen();
extern bool validateColumn (char input);
bool validateFoundation (char input);
bool validateMoveToFoundation (Card* toMove, Card* destination);
bool validateMoveToColumn (Card* toMove, Card* destination);
void moveSingleCard (Card* toMoveColumn, Card* destination);
void moveListOfCards (Card* first, Card* fromDummy, Card* toDummy);
bool checkWin (Board* gameboard);
void run_game();

#endif //MACHIN_PROJECT2_GAME_H
