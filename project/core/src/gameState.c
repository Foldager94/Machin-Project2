#include <stdlib.h>
#include "board.h"
#include "gameState.h"
#include <stdio.h>


GameState* initGameState(){
    GameState* gameState = malloc(sizeof(GameState));
    gameState->board=NULL;
    gameState->next=NULL;
    gameState->previuse=NULL;
}

void saveGameState(Board* board, GameState* destination){
    GameState* gameState = malloc(sizeof(GameState));
    gameState->board = board;
    gameState->next = destination;
    gameState->previuse = destination->previuse;
    destination->previuse->next = gameState;
    destination->previuse = gameState;

};

void changeGameState(Board* board, GameState* gameState, int gameStateCounter){
    GameState* currentGameState = gameState->previuse;
    for(int i = 0; i<gameStateCounter;i++){
        currentGameState = currentGameState->previuse;
    }
    for (int i = 0; i < 7; i++) {
        board->columns[i] = currentGameState->board->columns[i];
        if(i < 4){
            board->foundations[i] = currentGameState->board->foundations[i];
        }
    }
}
