#ifndef MACHIN_PROJECT2_GAMESTATE_H
#define MACHIN_PROJECT2_GAMESTATE_H

#include "board.h"

typedef struct gameState{
    Board* board;
    struct gameState* next;
    struct gameState* previous;
}GameState;

extern void saveGameState(Board* board, GameState* destination);
extern GameState* initGameState();
extern void changeGameState(Board* board, GameState* gameState, int gameStateCounter);
extern void removeGameState(GameState* gameState, int gameStateCounter);
extern bool isAtBeginig(GameState* gameState, int gameStateCounter);
#endif //MACHIN_PROJECT2_GAMESTATE_H
