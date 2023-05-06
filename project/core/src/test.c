#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "deck.h"
#include "card.h"

/*void testLoadFile(){
    char *fileContent = "AC\n2C\n3C\n4C\n5C\n6C\n7C\n8C\n9C\nTC\nJC\nQC\nKC\nAD\n2D\n3D\n4D\n5D\n6D\n7D\n8D\n9D\nTD\nJD\nQD\nKD\nAH\n2H\n3H\n4H\n5H\n6H\n7H\n8H\n9H\nTH\nJH\nQH\nKH\nAS\n2S\n3S\n4S\n5S\n6S\n7S\n8S\n9S\nTS\nJS\nQS\nKS\n";
    FILE *fp;
    fp = fopen("test", "w");
    if (fp == NULL) {
        printf("testLoadFile Error: preparing file failed on opening the file\n");
        return;
    };
    fprintf(fp, "%s", fileContent);
    fclose(fp);

    char* expectedOutput ="AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AD 2D 3D 4D 5D 6D 7D 8D 9D TD JD QD KD AH 2H 3H 4H 5H 6H 7H 8H 9H TH JH QH KH AS 2S 3S 4S 5S 6S 7S 8S 9S TS JS QS KS ";
    char* output = loadFile("test");
    remove("test");

    assert(strcmp(output, expectedOutput) == 0);
    free(output);
    printf("test: Loadfile - Passed\n");
}*/

void testCreateDeck(){
    char* input ="AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AD 2D 3D 4D 5D 6D 7D 8D 9D TD JD QD KD AH 2H 3H 4H 5H 6H 7H 8H 9H TH JH QH KH AS 2S 3S 4S 5S 6S 7S 8S 9S TS JS QS KS ";
    int numCards = strlen(input) / 3;
    Card* output = createDeck(input);
    int count = 0;
    Card* currentCard = output->next;
    for (int i = 0; i < numCards; i++){
        if(currentCard->cardSuit != ' '){
            count++;
        };
        currentCard = currentCard->next;
    }
    freeDeck(output);
    assert(count == numCards);
    printf("test: CreateDeck - Passed\n");
}

void testShuffleDeck(){
    char* inputString ="AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AD 2D 3D 4D 5D 6D 7D 8D 9D TD JD QD KD AH 2H 3H 4H 5H 6H 7H 8H 9H TH JH QH KH AS 2S 3S 4S 5S 6S 7S 8S 9S TS JS QS KS ";
    Card* input = createDeck(inputString);

    shuffleDeck(input, 26);
    char* firstExpectedOutput = "AC AH 2C 2H 3C 3H 4C 4H 5C 5H 6C 6H 7C 7H 8C 8H 9C 9H TC TH JC JH QC QH KC KH AD AS 2D 2S 3D 3S 4D 4S 5D 5S 6D 6S 7D 7S 8D 8S 9D 9S TD TS JD JS QD QS KD KS ";
    assert(strcmp(deckToString(input, false), firstExpectedOutput) == 0);

    shuffleDeck(input, 13);
    char* secoundExpectedOutput ="AC 7H AH 8C 2C 8H 2H 9C 3C 9H 3H TC 4C TH 4H JC 5C JH 5H QC 6C QH 6H KC 7C KH AD AS 2D 2S 3D 3S 4D 4S 5D 5S 6D 6S 7D 7S 8D 8S 9D 9S TD TS JD JS QD QS KD KS ";
    assert(strcmp(deckToString(input, false), secoundExpectedOutput) == 0);

    shuffleDeck(input, 39);
    char* thirdExpectedOutput ="AC 7S 7H 8D AH 8S 8C 9D 2C 9S 8H TD 2H TS 9C JD 3C JS 9H QD 3H QS TC KD 4C KS TH 4H JC 5C JH 5H QC 6C QH 6H KC 7C KH AD AS 2D 2S 3D 3S 4D 4S 5D 5S 6D 6S 7D ";
    assert(strcmp(deckToString(input, false), thirdExpectedOutput) == 0);

    freeDeck(input);
    printf("test: ShuffleDeck - Passed\n");
}

void testShuffleDeckRandom(){
    char* inputString ="AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AD 2D 3D 4D 5D 6D 7D 8D 9D TD JD QD KD AH 2H 3H 4H 5H 6H 7H 8H 9H TH JH QH KH AS 2S 3S 4S 5S 6S 7S 8S 9S TS JS QS KS ";
    Card* input = createDeck(inputString);
    shuffleDeckRandom(input);
    assert(strcmp(deckToString(input, false), inputString) != 0);
    freeDeck(input);
    printf("test: ShuffleDeckRandom - Passed\n");

}
void testASCII_to_numeric(){
    assert(ASCII_to_numeric((int)'A') == 1);
    assert(ASCII_to_numeric((int)'T') == 10);
    assert(ASCII_to_numeric((int)'J') == 11);
    assert(ASCII_to_numeric((int)'Q') == 12);
    assert(ASCII_to_numeric((int)'K') == 13);
    assert(ASCII_to_numeric((int)'2') == 2);
    assert(ASCII_to_numeric((int)'3') == 3);
    assert(ASCII_to_numeric((int)'4') == 4);
    assert(ASCII_to_numeric((int)'5') == 5);
    assert(ASCII_to_numeric((int)'6') == 6);
    assert(ASCII_to_numeric((int)'7') == 7);
    assert(ASCII_to_numeric((int)'8') == 8);
    assert(ASCII_to_numeric((int)'9') == 9);
    printf("test: ASCII_to_numeric - Passed\n");

}



void runTests(){
    //testLoadFile();
    testCreateDeck();
    testShuffleDeck();
    testShuffleDeckRandom();
    testASCII_to_numeric();
}