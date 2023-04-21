struct card
{
    bool isFlipped;
    char cardValue[2];
    char cardSuit;
    struct card *previous;
    struct card *next;
};