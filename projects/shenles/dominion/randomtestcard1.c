#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define NUM_RUNS 5 

void myAssert(int myCondition) {

    if (!myCondition) {
        printf("FAILED TEST: ");
    } else {
        printf("PASSED TEST: ");
    }
}

int main() {
    srand(time(NULL));
    int numPlayers, currPlayer;
    int seed;
    struct gameState game, testgame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    seed = rand() % 100;
    int currtest;
    int expNumDrawn=1;
    int expAddedActions=2;
    int expNumDiscarded=1; 
    int expDiscardCt, expHandCt, expActions, expDeckCt;
    int decksize, handsize, discardsize;
    int handPos=0;
    int run;
    int pl;
    for (run=0; run < NUM_RUNS; run++) {
        numPlayers = rand() % MAX_PLAYERS + 1;            
        initializeGame(numPlayers, k, seed, &testgame);
        memcpy(&game, &testgame, sizeof(struct gameState));
        for (pl=0; pl < numPlayers; pl++) {
            currPlayer = pl;
            decksize = game.deckCount[currPlayer];
            handsize = game.handCount[currPlayer];
            discardsize = game.discardCount[currPlayer];
            expActions = game.numActions + expAddedActions;
            expDiscardCt = discardsize + expNumDiscarded;
            expHandCt = handsize + expNumDrawn - expNumDiscarded; 
            expDeckCt = decksize - expNumDrawn; 
            villageEffect(currPlayer, &testgame, handPos);
 
            printf("Checking player %d\n", currPlayer); 
            currtest = testgame.handCount[currPlayer] == expHandCt;
            myAssert(currtest);
            printf("hand count = %d, expected = %d\n", testgame.handCount[currPlayer], expHandCt);
            currtest = testgame.deckCount[currPlayer] == expDeckCt;
            myAssert(currtest);
            printf("deck count = %d, expected = %d\n", testgame.deckCount[currPlayer], expDeckCt);
            currtest = testgame.discardCount[currPlayer] == expDiscardCt;
            myAssert(currtest);
            printf("discard count = %d, expected = %d\n", testgame.discardCount[currPlayer], expDiscardCt);
            currtest = testgame.numActions == expActions;
            myAssert(currtest);
            printf("action count = %d, expected = %d\n", testgame.numActions, expActions); 
            currtest = testgame.supplyCount[estate] == game.supplyCount[estate];
            myAssert(currtest);
            printf("estate supply count = %d, expected = %d\n", testgame.supplyCount[estate], game.supplyCount[estate]);
            currtest = testgame.supplyCount[duchy] == game.supplyCount[duchy];
            myAssert(currtest);
            printf("duchy supply count = %d, expected = %d\n", testgame.supplyCount[duchy], game.supplyCount[duchy]);
            currtest = testgame.supplyCount[province] == game.supplyCount[province];
            myAssert(currtest);
            printf("province supply count = %d, expected = %d\n", testgame.supplyCount[province], game.supplyCount[province]);

        }  
    }
             

}

