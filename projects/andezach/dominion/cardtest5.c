#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
  int seed = 1000;
  int numPlayer = 2;
  int currentPlayer = 0;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  int result;

  printf("Successful Draw Card When Deck Has Cards: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  memcpy(&after, &before, sizeof(struct gameState));
  drawCard(currentPlayer, &after);
  printf("expected card count: %i, actual: %i\n", 
    before.handCount[currentPlayer] + 1,
    after.handCount[currentPlayer]);

  printf("Successful Draw Card When Deck Empty but Discard has Cards: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.deckCount[currentPlayer] = 0;
  before.discardCount[currentPlayer] = 1;
  before.discard[currentPlayer][0] = minion;
  memcpy(&after, &before, sizeof(struct gameState));
  drawCard(currentPlayer, &after);
  printf("expected card count: %i, actual: %i\n",
    before.handCount[currentPlayer] + 1,
    after.handCount[currentPlayer]);

  printf("Unsuccessful Draw Card When Deck and Discard are Empty: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.deckCount[currentPlayer] = 0;
  before.discardCount[currentPlayer] = 0;
  memcpy(&after, &before, sizeof(struct gameState));
  result = drawCard(currentPlayer, &after);
  printf("expected result and card count: -1, %i, actual: %i, %i\n",
    before.handCount[currentPlayer],
    result,
    after.handCount[currentPlayer]);
}
