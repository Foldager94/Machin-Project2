//
// Created by Christoffer on 08-05-2023.
//

#ifndef MACHIN_PROJECT2_GAMESTATE_H
#define MACHIN_PROJECT2_GAMESTATE_H

#include "board.h"

typedef struct gameState{
    Board* board;
    struct gameState* next;
    struct gameState* previuse;
}GameState;

extern void saveGameState(Board* board, GameState* destination);
extern GameState* initGameState();
extern void changeGameState(Board* board, GameState* gameState, int gameStateCounter);
#endif //MACHIN_PROJECT2_GAMESTATE_H
