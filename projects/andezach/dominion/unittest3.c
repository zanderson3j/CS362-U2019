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
  int choice1, choice2, handPos, result;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  printf("Current Player Discards 1 of Revealed Card Plus Ambassador: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = ambassador; //put ambassador card in hand
  before.hand[currentPlayer][1] = minion; //put minion card in hand
  before.hand[currentPlayer][2] = minion; //put minion card in hand
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 1;
  choice2 = 1;
  handPos = 0;
  ambassadorEffect(currentPlayer, choice1, choice2, &after, handPos);
  printf("expected handCount: %i, actual: %i\n", before.handCount[currentPlayer] - 2, after.handCount[currentPlayer]);

  printf("Other Player Gains One of Revealed Card: ");
  printf("expected handCount and Last Card: %i:%i, actual: %i:%i\n", before.handCount[currentPlayer + 1] + 1, minion, after.handCount[currentPlayer + 1], after.hand[currentPlayer + 1][after.handCount[currentPlayer + 1] - 1]);

  printf("Current Player Tries to Discard Too Much: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = ambassador; //put ambassador card in hand
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 1;
  choice2 = 3;
  handPos = 0;
  result = ambassadorEffect(currentPlayer, choice1, choice2, &after, handPos);
  printf("expected result: -1, actual: %i\n", result);

  printf("Current Player Tries to Discard Too Little: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = ambassador; //put ambassador card in hand
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 1;
  choice2 = -1;
  handPos = 0;
  result = ambassadorEffect(currentPlayer, choice1, choice2, &after, handPos);
  printf("expected result: -1, actual: %i\n", result);

  printf("Current Player Tries to Use Played Card as Revealed Card: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = ambassador; //put ambassador card in hand
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 0;
  choice2 = 1;
  handPos = 0;
  result = ambassadorEffect(currentPlayer, choice1, choice2, &after, handPos);
  printf("expected result: -1, actual: %i\n", result);
}
