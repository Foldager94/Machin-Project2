struct card
{
    bool isFlipped;
    char cardValue[2];
    char cardSuit;
    card *previous;
    card *next;
};