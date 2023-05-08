#include <string.h>
#include "game.h"
#include "test.h"

const char argTest[] = "-test";

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], argTest) == 0) {
            runTests();
            return 0;
        }
    }

    run_game();
    return 0;
}

