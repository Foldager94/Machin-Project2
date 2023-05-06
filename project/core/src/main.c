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

/*int stringToInt(char* str) {
    int result = 0;
    int sign = 1;
    // Checks if the given string is negativ - Sets sign ti -1 if it is
    if (*str == '-') {
        sign = -1;
        str++;
    }
    // Iterates through the String, and adds its Ascii Value to result
    while (*str != '\0') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}*/


 /*int SL(Card* deck, char* split){
     int splitInt;
     if(strcmp(split, "") == 0){
         splitInt = randomNumber(53);
     }else{
         splitInt = stringToInt(split);
         if(splitInt < 53 && 0 > splitInt){
             printf("Fejl: Tallet er 0 eller negativ, eller større end mængden af kort i dækket");
             return 1;
         }
     };
     shuffleDeck(deck, splitInt);
     return 0;
 }*/

