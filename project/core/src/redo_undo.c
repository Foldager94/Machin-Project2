#include <stdio.h>
#include <stdlib.h>
#define MAX_MOVES 100


typedef struct {
    int score;
    char deck[52];
    // ...
} GameState;

typedef struct {
    GameState* data[MAX_MOVES];
    int top;
} GameStack;


GameState* newGameState() {
    GameState* newState = malloc(sizeof(GameState));
    newState->score = 0;
    // ...
    return newState;
}

// Initialize the game stack
void initGameStack(GameStack* stack) {
    stack->top = -1;
}


void pushGameState(GameStack* stack, GameState* state) {
    if (stack->top < MAX_MOVES - 1) {
        stack->top++;
        stack->data[stack->top] = state;
    }
}


GameState* popGameState(GameStack* stack) {
    if (stack->top >= 0) {
        GameState* state = stack->data[stack->top];
        stack->top--;
        return state;
    }
    return NULL;
}
// int main() {
//    GameStack stack;
 //   initGameStack(&stack);
    // Initialize the game state
//    GameState* gameState = newGameState();
    // ...
    // Push the initial game state onto the stack
 //   pushGameState(&stack, gameState);
    // Perform some game moves
    // ...
    // Undo the last move
//    GameState* prevState = popGameState(&stack);
//    if (prevState != NULL) {
  //      gameState = prevState;
        // Restore the game state to the previous state
        // ...
 //   }
    // Redo the last move
//    if (stack.top < MAX_MOVES - 1) {
//        GameState* nextState = stack.data[stack.top + 1];
 //       if (nextState != NULL) {
 //           gameState = nextState;
            // Restore the game state to the next state
            // ...
  //          stack.top++;
//        }
//    }
 //   return 0;
// }