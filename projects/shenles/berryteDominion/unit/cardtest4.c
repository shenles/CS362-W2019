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

void testVillage() {

    int handpos=0, choice1=-1, choice2=-1, choice3=-1, bonus=0;
    int seed=1000;
    int numPlayers=2;
    int currPlayer=0;
    struct gameState game, testgame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    initializeGame(numPlayers, k, seed, &game);
    int currtest=0;
    int otherPlayer = 1;
    int numDrawn=1;
    int numDiscarded=1;
    int numShuffled=0;
    int addedActions=2;
    printf("-------- Testing Village Card -------\n");
    printf("------Test 0: correct num of actions------\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &testgame, handpos, &bonus);
    currtest = testgame.numActions == game.numActions + addedActions;
    myAssert(currtest);
    printf("num actions = %d, expected = %d\n", testgame.numActions, game.numActions + addedActions);

    printf("-------Test 1: correct hand size------\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    choice1=1;
    cardEffect(village, choice1, choice2, choice3, &testgame, handpos, &bonus);
    currtest = testgame.handCount[currPlayer] == game.handCount[currPlayer] + numDrawn - numDiscarded;
    myAssert(currtest);
    printf("hand count = %d, expected = %d\n", testgame.handCount[currPlayer], game.handCount[currPlayer] + numDrawn - numDiscarded);

    printf("-------Test 2: correct deck size------\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &testgame, handpos, &bonus);
    currtest = testgame.deckCount[currPlayer] == game.deckCount[currPlayer] - numDrawn + numShuffled;
    myAssert(currtest);
    printf("deck count = %d, expected = %d\n", testgame.deckCount[currPlayer], game.deckCount[currPlayer] - numDrawn + numShuffled);

    printf("-------Test 3: correct discard size------\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &testgame, handpos, &bonus);
    currtest = testgame.discardCount[currPlayer] == game.discardCount[currPlayer] + numDiscarded;
    myAssert(currtest);
    printf("discard count = %d, expected = %d\n", testgame.discardCount[currPlayer], game.discardCount[currPlayer] + numDiscarded);

    printf("-------Test 4: ensure no effect on other player hand----\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &testgame, handpos, &bonus);
    currtest = testgame.handCount[otherPlayer] == game.handCount[otherPlayer];
    myAssert(currtest);
    printf("other player hand count = %d, expected = %d\n", testgame.handCount[otherPlayer], game.handCount[otherPlayer]);

    printf("-------Test 5: ensure no effect on other player deck------\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &testgame, handpos, &bonus);
    currtest = testgame.deckCount[otherPlayer] == game.deckCount[otherPlayer];
    myAssert(currtest);
    printf("other player deck count = %d, expected = %d\n", testgame.deckCount[otherPlayer], game.deckCount[otherPlayer]);

    printf("------Test 6: ensure no effect on victory card piles-----\n");
    memcpy(&testgame, &game, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &testgame, handpos, &bonus);
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
    cardEffect(village, choice1, choice2, choice3, &testgame, handpos, &bonus);
    printf("------checking all piles-----\n");
    for (int i=0; i < 10; i++) {
        currtest = testgame.supplyCount[k[i]] == game.supplyCount[k[i]];
        myAssert(currtest);
    }

}

int main () {

    testVillage();
    return 0;
}

