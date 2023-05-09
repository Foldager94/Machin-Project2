#include <stdlib.h>
#include "../include/board.h"
#include "../include/gameState.h"

GameState* initGameState(){
    GameState* gameState = malloc(sizeof(GameState));
    gameState->board=NULL;
    gameState->next=NULL;
    gameState->previous=NULL;
}

void saveGameState(Board* board, GameState* destination){
    GameState* gameState = malloc(sizeof(GameState));
    gameState->board = board;
    gameState->next = destination;
    gameState->previous = destination->previous;
    destination->previous->next = gameState;
    destination->previous = gameState;

};

void changeGameState(Board* board, GameState* gameState, int gameStateCounter){
    GameState* currentGameState = gameState->previous;
    for(int i = 0; i<gameStateCounter;i++){
        currentGameState = currentGameState->previous;
    }
    for (int i = 0; i < 7; i++) {
        board->columns[i] = currentGameState->board->columns[i];
        if(i < 4){
            board->foundations[i] = currentGameState->board->foundations[i];
        }
    }
}
