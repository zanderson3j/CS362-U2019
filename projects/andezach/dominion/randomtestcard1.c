#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int testResults(int currentPlayer, int choice1, struct gameState *before, struct gameState *after, int result) {

  if (result == 0) {
    int i = 0;

    if (before->numBuys + 1 != after->numBuys) return 1;

    for (i = 0; i < before->handCount[currentPlayer]; ++i) {
      if (before->hand[currentPlayer][i] == baron) break;
    }

    if (i > before->handCount[currentPlayer]) return 1;

    if (choice1 == 1) {
      for (i = 0; i < before->handCount[currentPlayer]; ++i) {
        if (before->hand[currentPlayer][i] == estate) {
          if (before->coins + 4 != after->coins) {
            return 1;
          } else if (before->discardCount[currentPlayer] + 1 != after->discardCount[currentPlayer]) {
            return 1;
          } else if (before->handCount[currentPlayer] - 1 != after->handCount[currentPlayer]) {
            return 1;
          }
          break;
        }
      }

      if (i > before->handCount[currentPlayer]) {
        if (supplyCount(estate, before) > 0) {
          if (before->handCount[0] + 1 != after->handCount[0] || estate != after->hand[0][after->handCount[0] - 1]) {
            return 1;
          }
        } else if (before->handCount[0] != after->handCount[0]) {
          return 1;
        }

      }

    } else {
      if (supplyCount(estate, before) > 0) {
        if (before->handCount[0] + 1 != after->handCount[0] || estate != after->hand[0][after->handCount[0] - 1]) {
          return 1;
        }
      } else if (before->handCount[0] != after->handCount[0]) {
        return 1;
      }
    }

  } else {
    return 1;
  }

  return 0;
}

int main() {

  const int numOfTests = 2000;
  int currentPlayer;
  int choice1;
  int result;
  int failed = 0;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  srand(time(0));

  for (int i = 0; i < numOfTests; ++i) {
    currentPlayer = rand() % 2; //2 players
    choice1 = rand() % 2;
    memset(&before, 23, sizeof(struct gameState));
    initializeGame(2, k, rand(), &before);
    memcpy(&after, &before, sizeof(struct gameState));
    result = baronEffect(currentPlayer, choice1, &after);
    failed += testResults(currentPlayer, choice1, &before, &after, result);
  }

  printf("Failed %i out of %i.", failed, numOfTests);

  return 0;
}
