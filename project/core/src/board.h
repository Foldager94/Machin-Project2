#include <stdio.h>

#include "card.h"

struct board
{
    struct card columns[7];
    struct card foundations[4];
};
