cmake_minimum_required(VERSION 3.24)
project(Machin_Project2 C)

set(CMAKE_C_STANDARD 11)

include_directories(project/core/src)

add_executable(Machin_Project2
        project/core/src/board.h
        project/core/src/card.h
        project/core/src/commandLine.h
        project/core/src/main.c project/core/src/file_loader.c project/core/src/file_loader.h)
