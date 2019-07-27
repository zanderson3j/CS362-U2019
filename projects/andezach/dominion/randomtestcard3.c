#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int testResults(int currentPlayer, int nextPlayer, struct gameState *before, struct gameState *after, int *tributeRevealedCards, int result) {
  if (result == 0) {
    if ((before->discardCount[nextPlayer] + before->deckCount[nextPlayer]) <= 1) {
      if (before->deckCount[nextPlayer] > 0) {
        if(tributeRevealedCards[0] != before->deck[nextPlayer][before->deckCount[nextPlayer]-1]) {
          return 1;
        }
        if(before->deckCount - 1 != after->deckCount) {
          return 1;
        }
      } else if (before->discardCount[nextPlayer] > 0) {
        if(tributeRevealedCards[0] != before->discard[nextPlayer][state->discardCount[nextPlayer]-1]) {
          return 1;
        }
        if(before->discardCount - 1 != after->discardCount) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int main() {

  const int numOfTests = 2000;
  int currentPlayer = 0;
  int nextPlayer = 1;
  int tributeRevealedCards[2];
  int result;
  int failed = 0;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  srand(time(0));

  for (int i = 0; i < numOfTests; ++i) {
    memset(&before, 23, sizeof(struct gameState));
    initializeGame(2, k, rand(), &before);
    memcpy(&after, &before, sizeof(struct gameState));
    // result = tributeEffect(currentPlayer, nextPlayer, &after, tributeRevealedCards);
    // failed += testResults(currentPlayer, nextPlayer, &before, &after, tributeRevealedCards, result);
  }

  return 0;
}
