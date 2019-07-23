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
    
  }
}

int main() {

  const int numOfTests = 2000;
  int currentPlayer;
  int nextPlayer;
  int tributeRevealedCards[2];
  int result;
  int failed = 0;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  srand(time(0));

  for (int i = 0; i < numOfTests; ++i) {
    currentPlayer = rand() % 2; //2 players
    if (currentPlayer == 0) {
      nextPlayer = 1;
    } else {
      nextPlayer = 0;
    }
    for (int i = 0; i < 2; ++i) {
      tributeRevealedCards[i] = rand() % 28;
    }
    memset(&before, 23, sizeof(struct gameState));
    initializeGame(2, k, rand(), &before);
    memcpy(&after, &before, sizeof(struct gameState));
    result = tributeEffect(currentPlayer, nextPlayer, &after, tributeRevealedCards);
    failed += testResults(currentPlayer, nextPlayer, &before, &after, tributeRevealedCards, result);
  }

  return 0;
}
