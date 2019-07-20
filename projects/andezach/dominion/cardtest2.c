#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
  int seed = 1000;
  int numPlayer = 2;
  int nextPlayer = 1; //use next player since they have more cards
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  int result;

  printf("Different Card Order After Shuffle:\n");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  memcpy(&after, &before, sizeof(struct gameState));
  shuffle(nextPlayer, &after);
  printf("Before: ");
  for(int i = 0; i < before.deckCount[nextPlayer]; ++i) {
    printf("%i ", before.deck[nextPlayer][i]);
  }
  printf("\n");
  printf("After: ");
  for(int i = 0; i < after.deckCount[nextPlayer]; ++i) {
    printf("%i ", after.deck[nextPlayer][i]);
  }
  printf("\n");

  printf("Same Deck Count After Shuffle: ");
  printf("expected deck count: %i, actual: %i\n",
    before.deckCount[nextPlayer],
    after.deckCount[nextPlayer]);

  printf("Empty Deck Can't be Shuffled: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.deckCount[nextPlayer] = 0;
  memcpy(&after, &before, sizeof(struct gameState));
  result = shuffle(nextPlayer, &after);
  printf("expected result: -1, actual: %i\n", result);
}
