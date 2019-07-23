#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int testResults(int currentPlayer, int choice1, int choice2, struct gameState *before, struct gameState *after, int handPos, int result) {
  if (result == 0) {

    if (before->numActions + 1 != after->numActions) return 1;

    if (choice1 == choice2 || (choice1 < 0 || choice1 > 1) || (choice2 < 0 || choice2 > 1)) {
      return 1;
    } else if (choice1 == 1) {
      if (before->coins + 2 != after->coins) return 1;
    } else {
      for (int i = 0; i < before->numPlayers; ++i) {
        if (i == currentPlayer || before->handCount[i] > 4) {
          if (after->handCount[i] != 4) return 1;
        }
      }
    }

  } else {
    return 1;
  }
}

int main() {

  const int numOfTests = 2000;
  int currentPlayer;
  int choice1;
  int choice2;
  int handPos;
  int result;
  int failed = 0;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  srand(time(0));

  for (int i = 0; i < numOfTests; ++i) {
    currentPlayer = rand() % 2; //2 players
    choice1 = rand() % 2;
    choice2 = rand() % 2;
    handPos = rand() % 5;
    memset(&before, 23, sizeof(struct gameState));
    initializeGame(2, k, rand(), &before);
    memcpy(&after, &before, sizeof(struct gameState));
    result = minionEffect(currentPlayer, choice1, choice2, &after, handPos);
    failed += testResults(currentPlayer, choice1, choice2, &before, &after, handPos, result);
  }

  printf("Failed %i out of %i.", failed, numOfTests);

  return 0;
}
