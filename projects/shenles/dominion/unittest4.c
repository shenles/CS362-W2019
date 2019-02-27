#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void myAssert(int myCondition) {

    if (!myCondition) {
        printf("FAILED TEST \n");
    } else {
        printf("PASSED TEST \n");
    }
}

void testNumHandCards() {

    int seed=1000;
    int numPlayers=2;
    struct gameState game, testgame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    initializeGame(numPlayers, k, seed, &game);
    int currtest=0;
    int expected=0;
    int actual=0;
    printf("-----Testing numHandCards--------\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    testgame.whoseTurn = 1; 
    testgame.handCount[1] = 3;
    expected = 3; 
    actual = numHandCards(&testgame);
    currtest = actual == expected;
    myAssert(currtest);

}

int main () {

    testNumHandCards();
    return 0;
}
