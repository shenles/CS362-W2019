#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_RUNS 10 

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
    int currtest, expectedHandCt, expectedDeckCt, expectedDiscardCt;
    int nonTreasDrawn;
    int numRevealed;
    int drawntreasure, drawnTreasCt, actualTreas, expectedTreas;
    int decksize, handsize, discardsize, thisDraw;
    int run;
    int pl;
    for (run=0; run < NUM_RUNS; run++) {
        numPlayers = rand() % MAX_PLAYERS + 1;            
        initializeGame(numPlayers, k, seed, &testgame);
        memcpy(&game, &testgame, sizeof(struct gameState));
        int temphand[MAX_HAND];
        for (pl=0; pl < numPlayers; pl++) {
            drawntreasure=0;
            drawnTreasCt=0;
            actualTreas=0;
            expectedTreas=0;
            numRevealed=0;
            currPlayer = pl;
            decksize = game.deckCount[currPlayer];
            handsize = game.handCount[currPlayer];
            discardsize = game.discardCount[currPlayer];
            while (drawnTreasCt < 2 && numRevealed <= decksize + discardsize) {
                drawCard(currPlayer, &game);
                thisDraw = game.hand[currPlayer][game.handCount[currPlayer]-1];
                numRevealed++;
                if (thisDraw == copper || thisDraw == silver || thisDraw == gold) {
                   drawnTreasCt++;
                } else {
                   game.handCount[currPlayer] = game.handCount[currPlayer] - 1;
                   nonTreasDrawn++;
                }   
            }

            expectedDiscardCt = discardsize + nonTreasDrawn + 1;
            expectedHandCt = handsize + drawnTreasCt - 1; 
            expectedDeckCt = decksize - numRevealed; 
            
            for (int j=0; j<game.handCount[currPlayer]; j++) {
               if (game.hand[currPlayer][j] == copper || game.hand[currPlayer][j] == silver || game.hand[currPlayer][j] == gold) {
                  expectedTreas++;
               }
            }
                
            adventurerEffect(drawntreasure, &testgame, currPlayer, temphand);

            for (int m=0; m<testgame.handCount[currPlayer]; m++) {
               if (testgame.hand[currPlayer][m] == copper || testgame.hand[currPlayer][m] == silver || testgame.hand[currPlayer][m] == gold) {
                  actualTreas++;
               }
            }
 
            printf("Checking player %d\n", currPlayer); 
            currtest = testgame.handCount[currPlayer] == expectedHandCt;
            myAssert(currtest);
            printf("hand count = %d, expected = %d\n", testgame.handCount[currPlayer], expectedHandCt);
            currtest = testgame.deckCount[currPlayer] == expectedDeckCt;
            myAssert(currtest);
            printf("deck count = %d, expected = %d\n", testgame.deckCount[currPlayer], expectedDeckCt);
            currtest = testgame.discardCount[currPlayer] == expectedDiscardCt;
            myAssert(currtest);
            printf("discard count = %d, expected = %d\n", testgame.discardCount[currPlayer], expectedDiscardCt);
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
