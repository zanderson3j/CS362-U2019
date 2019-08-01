#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int printFailure(char *message, int currentPlayer, int choice1, struct gameState *before, struct gameState *after, int result) {
  printf("%s: currentPlayer-%i, choice1-%i, hand-%i %i %i %i %i, coins-%i->%i, result-%i\n",
            message,
            currentPlayer,
            choice1,
            before->hand[currentPlayer][0],
            before->hand[currentPlayer][1],
            before->hand[currentPlayer][2],
            before->hand[currentPlayer][3],
            before->hand[currentPlayer][4],
            before->coins,
            after->coins,
            result);
  return 1;
}

int testResults(int currentPlayer, int choice1, struct gameState *before, struct gameState *after, int result) {

  if (result == 0) {
    int i = 0;

    if (before->numBuys + 1 != after->numBuys) return printFailure("Number of Buys didn't INC", currentPlayer, choice1, before, after, result);

    for (i = 0; i < before->handCount[currentPlayer]; ++i) {
      if (before->hand[currentPlayer][i] == baron) break;
    }

    if (i > before->handCount[currentPlayer]) return printFailure("No Baron in hand", currentPlayer, choice1, before, after, result);

    if (choice1 == 1) {
      for (i = 0; i < before->handCount[currentPlayer]; ++i) {
        if (before->hand[currentPlayer][i] == estate) {
          if (before->coins + 4 != after->coins) {
            return printFailure("Didn't get 4 coins", currentPlayer, choice1, before, after, result);
          } else if (before->discardCount[currentPlayer] + 1 != after->discardCount[currentPlayer]) {
            return printFailure("Didn't discard estate properly", currentPlayer, choice1, before, after, result);
          } else if (before->handCount[currentPlayer] - 1 != after->handCount[currentPlayer]) {
            return printFailure("Didn't decrement hand count", currentPlayer, choice1, before, after, result);
          }
          break;
        }
      }

      if (i > before->handCount[currentPlayer]) {
        if (supplyCount(estate, before) > 0) {
          if (before->handCount[0] + 1 != after->handCount[0] || estate != after->hand[0][after->handCount[0] - 1]) {
            return printFailure("Didn't pick up estate after not having one to discard", currentPlayer, choice1, before, after, result);
          }
        } else if (before->handCount[0] != after->handCount[0]) {
          return printFailure("No estate to pick up, but hand count changed", currentPlayer, choice1, before, after, result);
        }

      }

    } else {
      if (supplyCount(estate, before) > 0) {
        if (before->handCount[0] + 1 != after->handCount[0] || estate != after->hand[0][after->handCount[0] - 1]) {
          return printFailure("Didn't pick up estate", currentPlayer, choice1, before, after, result);
        }
      } else if (before->handCount[0] != after->handCount[0]) {
        return printFailure("No estate to pick up, but hand count changed", currentPlayer, choice1, before, after, result);
      }
    }

  } else {
    return printFailure("Result not 0", currentPlayer, choice1, before, after, result);
  }

  return 0;
}

int main() {

  const int numOfTests = 2000;
  int currentPlayer = 0;
  int choice1;
  int result;
  int failed = 0;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  srand(time(0));

  for (int i = 0; i < numOfTests; ++i) {
    choice1 = rand() % 2;
    memset(&before, 23, sizeof(struct gameState));
    initializeGame(2, k, rand(), &before);
    if (rand() % 100 == 1) {
      before.supplyCount[estate] = 0;
    }
    memcpy(&after, &before, sizeof(struct gameState));
    result = playBaron(choice1, &after, currentPlayer);
    failed += testResults(currentPlayer, choice1, &before, &after, result);
  }

  printf("Failed %i out of %i.", failed, numOfTests);

  return 0;
}
