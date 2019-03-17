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

void testIsGameOver() {

    int seed=1000;
    int numPlayers=2;
    struct gameState game, testgame, testgame2, testgame3;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    initializeGame(numPlayers, k, seed, &game);
    memcpy(&testgame, &game, sizeof(struct gameState));
    int currtest=0;
    int expectedState = 0;
    int actualState = 0;
    printf("-----Testing IsGameOver--------\n");
    // test province pile empty case 
    testgame.supplyCount[province] = 0;
    actualState = isGameOver(&testgame); 
    expectedState = 1;
    currtest = actualState == expectedState; 
    myAssert(currtest);
    // test 3 supply piles empty case 
    memcpy(&testgame2, &game, sizeof(struct gameState));
    testgame2.supplyCount[estate] = 0;
    testgame2.supplyCount[duchy] = 0;
    testgame2.supplyCount[silver] = 0;
    actualState = isGameOver(&testgame2);
    expectedState = 1;
    currtest = actualState == expectedState; 
    myAssert(currtest);
    // test to make sure game is not registered as over
    // when it is not over
    memcpy(&testgame3, &game, sizeof(struct gameState));
    actualState = isGameOver(&testgame3);
    expectedState = 0;
    currtest = actualState == expectedState; 
    myAssert(currtest); 
}

int main () {
    testIsGameOver();
    return 0; 
}
