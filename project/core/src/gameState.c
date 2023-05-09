#include <stdlib.h>
#include "../include/board.h"
#include "../include/gameState.h"
#include "../include/deck.h"

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
    Board* newBoard = makeBoardCopy(currentGameState->board);
    for (int i = 0; i < 7; i++) {
        board->columns[i] = newBoard->columns[i];
        if(i < 4){
            board->foundations[i] = newBoard->foundations[i];
        }
    }
}

void freeGameState(GameState* gameState){
    for(int i = 0; i<7; i++){
        if(i<4){
            freeDeck(gameState->board->foundations[i]);
        }
        freeDeck(gameState->board->columns[i]);
    }
    free(gameState);
}

void removeGameState(GameState* gameState, int gameStateCounter){
    GameState* currentGameState = gameState->previous;
    for(int i = 0; i < gameStateCounter-1; i++){
        currentGameState = currentGameState->previous;
    }

    gameState->previous = currentGameState->previous;
    currentGameState->previous->next = gameState;

    while(true){
        if(currentGameState->board==NULL){
            break;
        }
        GameState* tmp;
        tmp = currentGameState->next;
        freeGameState(currentGameState);
        currentGameState = tmp;
    }
}



bool isAtBeginig(GameState* gameState, int gameStateCounter){
    GameState* currentGameState = gameState->previous;
    for(int i = 0; i < gameStateCounter; i++){
        currentGameState = currentGameState->previous;
        if(currentGameState->board==NULL){
            return false;
        }
    }
    return true;
}