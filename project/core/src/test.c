#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../include/deck.h"

Card* create_test_deck(){
    char *fileContent = "AC\n2C\n3C\n4C\n5C\n6C\n7C\n8C\n9C\nTC\nJC\nQC\nKC\nAD\n2D\n3D\n4D\n5D\n6D\n7D\n8D\n9D\nTD\nJD\nQD\nKD\nAH\n2H\n3H\n4H\n5H\n6H\n7H\n8H\n9H\nTH\nJH\nQH\nKH\nAS\n2S\n3S\n4S\n5S\n6S\n7S\n8S\n9S\nTS\nJS\nQS\nKS\n";
    FILE *fp;
    fp = fopen("test", "w");
    if (fp == NULL) {
        printf("testLoadFile Error: preparing file failed on opening the file\n");
        return NULL;
    };
    fprintf(fp, "%s", fileContent);
    fclose(fp);

    Card* deck = initList();
    loadDeck("test", deck);
    remove("test");
    return deck;
}

// LD test
void test_load_deck(){
    //Create test file with cards
    char *fileContent = "AC\n2C\n3C\n4C\n5C\n6C\n7C\n8C\n9C\nTC\nJC\nQC\nKC\nAD\n2D\n3D\n4D\n5D\n6D\n7D\n8D\n9D\nTD\nJD\nQD\nKD\nAH\n2H\n3H\n4H\n5H\n6H\n7H\n8H\n9H\nTH\nJH\nQH\nKH\nAS\n2S\n3S\n4S\n5S\n6S\n7S\n8S\n9S\nTS\nJS\nQS\nKS\n";
    FILE *fp;
    fp = fopen("test", "w");
    if (fp == NULL) {
        printf("testLoadFile Error: preparing file failed on opening the file\n");
        return;
    };
    fprintf(fp, "%s", fileContent);
    fclose(fp);

    Card* deck = initList();
    loadDeck("test", deck);
    remove("test");

    Card* currentCard = deck->next;
    int count = 0;
    for (int i = 0; i < 52; i++){
        if(currentCard->cardSuit != ' '){
            count++;
        };
        currentCard = currentCard->next;
    }
    assert(count == 52);

    char* expectedOutput ="AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AD 2D 3D 4D 5D 6D 7D 8D 9D TD JD QD KD AH 2H 3H 4H 5H 6H 7H 8H 9H TH JH QH KH AS 2S 3S 4S 5S 6S 7S 8S 9S TS JS QS KS ";
    assert(strcmp(deckToString(deck, false), expectedOutput) == 0);
    freeDeck(deck);
    printf("(LD)loadDeck - Passed\n");
}


// SL test
void test_shuffle_deck(){
    Card* input = create_test_deck();

    shuffleDeck(input, 26);
    char* firstExpectedOutput = "AC AH 2C 2H 3C 3H 4C 4H 5C 5H 6C 6H 7C 7H 8C 8H 9C 9H TC TH JC JH QC QH KC KH AD AS 2D 2S 3D 3S 4D 4S 5D 5S 6D 6S 7D 7S 8D 8S 9D 9S TD TS JD JS QD QS KD KS ";
    assert(strcmp(deckToString(input, false), firstExpectedOutput) == 0);

    shuffleDeck(input, 13);
    char* secoundExpectedOutput ="AC 7H AH 8C 2C 8H 2H 9C 3C 9H 3H TC 4C TH 4H JC 5C JH 5H QC 6C QH 6H KC 7C KH AD AS 2D 2S 3D 3S 4D 4S 5D 5S 6D 6S 7D 7S 8D 8S 9D 9S TD TS JD JS QD QS KD KS ";
    assert(strcmp(deckToString(input, false), secoundExpectedOutput) == 0);

    shuffleDeck(input, 39);
    char* thirdExpectedOutput ="AC 7S 7H 8D AH 8S 8C 9D 2C 9S 8H TD 2H TS 9C JD 3C JS 9H QD 3H QS TC KD 4C KS TH 4H JC 5C JH 5H QC 6C QH 6H KC 7C KH AD AS 2D 2S 3D 3S 4D 4S 5D 5S 6D 6S 7D ";
    assert(strcmp(deckToString(input, false), thirdExpectedOutput) == 0);

    //clean up
    freeDeck(input);

    printf("(SL)shuffle_deck - Passed\n");
}

// SR test
void test_shuffle_deck_random(){

    Card* input = create_test_deck();
    shuffleDeckRandom(input);

    char* inputString ="AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AD 2D 3D 4D 5D 6D 7D 8D 9D TD JD QD KD AH 2H 3H 4H 5H 6H 7H 8H 9H TH JH QH KH AS 2S 3S 4S 5S 6S 7S 8S 9S TS JS QS KS ";
    assert(strcmp(deckToString(input, false), inputString) != 0);

    //clean up
    freeDeck(input);

    printf("(SR)shuffle_deck_random - Passed\n");

}
void testASCII_to_numeric(){
    assert(asciiToNumeric((int) 'A') == 1);
    assert(asciiToNumeric((int) 'T') == 10);
    assert(asciiToNumeric((int) 'J') == 11);
    assert(asciiToNumeric((int) 'Q') == 12);
    assert(asciiToNumeric((int) 'K') == 13);
    assert(asciiToNumeric((int) '2') == 2);
    assert(asciiToNumeric((int) '3') == 3);
    assert(asciiToNumeric((int) '4') == 4);
    assert(asciiToNumeric((int) '5') == 5);
    assert(asciiToNumeric((int) '6') == 6);
    assert(asciiToNumeric((int) '7') == 7);
    assert(asciiToNumeric((int) '8') == 8);
    assert(asciiToNumeric((int) '9') == 9);
    printf("asciiToNumeric - Passed\n");

}

//SD test
void test_save_deck(){
    //Create deck from file
    Card* deckExpectet = create_test_deck();

    saveDeckToFile(deckExpectet, "saved_deck");
    Card* deck = initList();
    loadDeck("saved_deck", deck);

    Card* current1 = deckExpectet;
    Card* current2 = deck;

    for(int i = 0; i <= 52; i++){
        assert(deckExpectet->cardValue == deck->cardValue);
        assert(deckExpectet->cardSuit == deck->cardSuit);
        current1 = current1 ->next;
        current2 = current2 ->next;
    }

    //clean up
    remove("saved_deck");
    freeDeck(deck);
    freeDeck(deckExpectet);

    printf("(SD)save_deck - Passed\n");
}



void runTests(){
    printf("Test:\n");
    test_load_deck();
    test_shuffle_deck();
    test_shuffle_deck_random();
    test_save_deck();
    testASCII_to_numeric();
}