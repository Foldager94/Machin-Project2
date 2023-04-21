#include <stdbool.h>

struct card{
    bool isFlipped;
    char cardValue;
    char cardSuit;
    struct card *previous;
    struct card *next;
};