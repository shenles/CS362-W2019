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

void testAdventurer() {

    int handpos=0, choice1=-1, choice2=-1, choice3=-1, bonus=0;
    int seed=1000;
    int numPlayers=2;
    int currPlayer=0;
    struct gameState game, testgame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    initializeGame(numPlayers, k, seed, &game);
    int currtest=0;
    int otherPlayer = 1;
    int drawnTreasCt = 0;
    int numRevealed = 0;
    int nonTreasDrawn = 0;
    int decksize=0;
    int handsize=0;
    int discardsize=0;
    int thisDraw=0;
    printf("-------- Testing Adventurer Card -------\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    choice1=1;
    cardEffect(adventurer, choice1, choice2, choice3, &testgame, handpos, &bonus);
    decksize = game.deckCount[currPlayer];
    discardsize = game.discardCount[currPlayer];
    handsize = game.handCount[currPlayer];

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
    int actualTreas=0, expectedTreas=0;
    int expectedDiscardCt = discardsize + nonTreasDrawn + 1;
    int expectedHandCt = handsize + drawnTreasCt - 1; 
    int expectedDeckCt = decksize - numRevealed; 
    printf("-----Test 0: correct treasure amount-----\n"); 
    for (int j=0; j<testgame.handCount[currPlayer]; j++) {
        if (testgame.hand[currPlayer][j] == copper || testgame.hand[currPlayer][j] == silver || testgame.hand[currPlayer][j] == gold) {
        actualTreas++;
        } 
    }

    for (int j=0; j<game.handCount[currPlayer]; j++) {
        if (game.hand[currPlayer][j] == copper || game.hand[currPlayer][j] == silver || game.hand[currPlayer][j] == gold) {
        expectedTreas++;
        }
    }

    currtest = actualTreas == expectedTreas;
    myAssert(currtest);
    printf("treasure in hand = %d, expected = %d\n", actualTreas, expectedTreas); 

    printf("-------Test 1: correct hand size------\n");
    currtest = testgame.handCount[currPlayer] == expectedHandCt;
    myAssert(currtest);
    printf("hand count = %d, expected = %d\n", testgame.handCount[currPlayer], expectedHandCt);

    printf("-------Test 2: correct deck size------\n");
    currtest = testgame.deckCount[currPlayer] == expectedDeckCt;
    myAssert(currtest);
    printf("deck count = %d, expected = %d\n", testgame.deckCount[currPlayer], expectedDeckCt);

    printf("-------Test 3: correct discard size------\n");
    currtest = testgame.discardCount[currPlayer] == expectedDiscardCt;
    myAssert(currtest);
    printf("discard count = %d, expected = %d\n", testgame.discardCount[currPlayer], expectedDiscardCt);

    printf("-------Test 4: ensure no effect on other player hand----\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testgame, handpos, &bonus);
    currtest = testgame.handCount[otherPlayer] == game.handCount[otherPlayer];
    myAssert(currtest);
    printf("other player hand count = %d, expected = %d\n", testgame.handCount[otherPlayer], game.handCount[otherPlayer]);

    printf("-------Test 5: ensure no effect on other player deck------\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testgame, handpos, &bonus);
    currtest = testgame.deckCount[otherPlayer] == game.deckCount[otherPlayer];
    myAssert(currtest);
    printf("other player deck count = %d, expected = %d\n", testgame.deckCount[otherPlayer], game.deckCount[otherPlayer]);

    printf("------Test 6: ensure no effect on victory card piles-----\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testgame, handpos, &bonus);
    printf("------checking estate pile-----\n");
    currtest = testgame.supplyCount[estate] == game.supplyCount[estate];
    myAssert(currtest);
    printf("------checking duchy pile-----\n");
    currtest = testgame.supplyCount[duchy] == game.supplyCount[duchy];
    myAssert(currtest);
    printf("------checking province pile-----\n");
    currtest = testgame.supplyCount[province] == game.supplyCount[province];
    myAssert(currtest);

    printf("------Test 7: ensure no effect on kingdom card piles-----\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testgame, handpos, &bonus);
    printf("------checking all piles-----\n");
    for (int i=0; i < 10; i++) {
        currtest = testgame.supplyCount[k[i]] == game.supplyCount[k[i]];
        myAssert(currtest);
    }
}

int main () {

    testAdventurer();
    return 0;
}

