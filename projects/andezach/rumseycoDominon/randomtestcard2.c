#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int printFailure(char *message, int currentPlayer, int choice1, int choice2, struct gameState *before, struct gameState *after, int handPos, int result) {
  printf("%s: currentPlayer-%i, choice1-%i, choice2-%i, hand-%i %i %i %i %i, coins-%i->%i, result-%i\n",
            message,
            currentPlayer,
            choice1,
            choice2,
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

int testResults(int currentPlayer, int choice1, int choice2, struct gameState *before, struct gameState *after, int handPos, int result) {
  if (result == 0) {
    int i = 0;

    if (before->numActions + 1 != after->numActions) return printFailure("Didn't increment actions", currentPlayer, choice1, choice2, before, after, handPos, result);

    for (i = 0; i < before->handCount[currentPlayer]; ++i) {
      if (before->hand[currentPlayer][i] == minion) break;
    }

    if (i > before->handCount[currentPlayer]) return printFailure("No minion in hand", currentPlayer, choice1, choice2, before, after, handPos, result);

    if (choice1 == choice2 || (choice1 < 0 || choice1 > 1) || (choice2 < 0 || choice2 > 1)) {
      return printFailure("Invalid choice", currentPlayer, choice1, choice2, before, after, handPos, result);
    } else if (choice1 == 1) {
      if (before->coins + 2 != after->coins) return printFailure("Didn't add coins", currentPlayer, choice1, choice2, before, after, handPos, result);
      for (i = 0; i < before->numPlayers; ++i) {
        if (before->handCount[i] != after->handCount[i] && i != currentPlayer) return printFailure("Hand count changed for other players", currentPlayer, choice1, choice2, before, after, handPos, result);
      }
    } else {
      for (i = 0; i < before->numPlayers; ++i) {
        if (i == currentPlayer || before->handCount[i] > 4) {
          if (after->handCount[i] != 4) return printFailure("Player didnt draw new hand", currentPlayer, choice1, choice2, before, after, handPos, result);
        } else if (before->handCount[i] != after->handCount[i]) {
          return printFailure("Player discarded hand with less than 5 cards", currentPlayer, choice1, choice2, before, after, handPos, result);
        }
      }
      if (before->coins != after->coins) return printFailure("Added coins with choice 2", currentPlayer, choice1, choice2, before, after, handPos, result);
    }

  } else {
    return printFailure("Result not 0", currentPlayer, choice1, choice2, before, after, handPos, result);
  }
  return 0;
}

int main() {

  const int numOfTests = 2000;
  int currentPlayer = 0;
  int choice1;
  int choice2;
  int handPos;
  int result;
  int failed = 0;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  srand(time(0));

  for (int i = 0; i < numOfTests; ++i) {
    choice1 = rand() % 2;
    choice2 = rand() % 2;
    handPos = rand() % 5;
    memset(&before, 23, sizeof(struct gameState));
    initializeGame(2, k, rand(), &before);
    memcpy(&after, &before, sizeof(struct gameState));
    result = playMinion(choice1, &after, 0, currentPlayer);
    failed += testResults(currentPlayer, choice1, choice2, &before, &after, handPos, result);
  }

  printf("Failed %i out of %i.", failed, numOfTests);

  return 0;
}
