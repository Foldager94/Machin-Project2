cmake_minimum_required(VERSION 3.24)
project(Machin-Project2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Machin-Project2 project/core/src/main.c project/core/src/board.c project/core/src/card.c project/core/src/deck.c project/core/src/test.c project/core/src/game.c project/core/src/commandLine.c project/core/include/game.h project/core/src/gameState.c)
