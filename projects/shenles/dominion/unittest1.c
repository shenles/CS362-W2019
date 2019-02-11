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

void testUpdateCoins() {

    int bonus=0;
    int seed=1000;
    int numPlayers=2;
    int currPlayer=0;
    struct gameState game, testgame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    initializeGame(numPlayers, k, seed, &game);
    int currtest=0;
    int expectedCoins=0; 
    printf("-----Testing UpdateCoins--------\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    updateCoins(currPlayer, &testgame, bonus);

    for (int j=0; j<game.handCount[currPlayer]; j++) {
        if (game.hand[currPlayer][j] == copper) {
            expectedCoins += 1;
        }
        else if (game.hand[currPlayer][j] == silver) {
            expectedCoins += 2;
        }
        else if (game.hand[currPlayer][j] == gold) {
            expectedCoins += 3;
        }
    }
    currtest = testgame.coins == expectedCoins;
    myAssert(currtest);
    printf("coins = %d, expected = %d\n", testgame.coins, expectedCoins);

}

int main () {
    testUpdateCoins();    
    return 0;
}
