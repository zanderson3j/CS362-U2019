#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
  int seed = 1000;
  int numPlayer = 2;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  printf("Turn Should go to Next Player: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  memcpy(&after, &before, sizeof(struct gameState));
  endTurn(&after);
  printf("expected turn: 1, actual: %i\n", after.whoseTurn);

  printf("Last Player Hand is Emptied and New Player is Full: \n");
  printf("Before: \n");
  printf("\tLast Player Hand: %i, New Player Hand: %i\n", before.handCount[0], before.handCount[1]);
  printf("After: \n");
  printf("\tLast Player Hand: %i, New Player Hand: %i\n", after.handCount[0], after.handCount[1]);

  printf("If Current Player is Last Player, Turn Goes to First Player: ");
  endTurn(&after);
  printf("expected turn: 0, actual: %i\n", after.whoseTurn);
}
