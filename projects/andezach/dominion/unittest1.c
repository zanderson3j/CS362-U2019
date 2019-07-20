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
  int choice1;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  //Test for choice of discarding estate card for 4 coins when estate card present.
  printf("Discard an Estate for 4 Coins: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = estate; //put estate card in hand
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 1;
  baronEffect(currentPlayer, choice1, &after);
  printf("expected coins: %i, actual: %i\n", before.coins + 4, after.coins);

  //Test the number of buys increases by one.
  printf("Increase Card Buys by One: ");
  printf("expected numBuys: %i, actual: %i\n", before.numBuys + 1, after.numBuys);

  //Test not discarding an estate card results in picking one up.
  printf("Pick Up An Estate: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 0;
  baronEffect(currentPlayer, choice1, &after);
  printf("expected handCount and last card: %i:%i, actual: %i:%i\n", before.handCount[0] + 1, estate, after.handCount[0], after.hand[0][after.handCount[0] - 1]);

  //Test not having an estate to discard results in picking one up.
  printf("Pick Up an Estate if None to Discard: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  for(int i = 0; i < before.handCount[currentPlayer]; ++i) {
    if (before.hand[currentPlayer][i] == estate) before.hand[currentPlayer][i] = tribute;
  }
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 1;
  baronEffect(currentPlayer, choice1, &after);
  printf("expected handCount and last card: %i:%i, actual: %i:%i\n", before.handCount[0] + 1, estate, after.handCount[0], after.hand[0][after.handCount[0] - 1]);

  printf("Don't Gain Coins if no Estate to Discard: ");
  printf("expected coins: %i, actual: %i\n", before.coins, after.coins);
}
