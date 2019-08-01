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

  printf("Trade Copper for Silver: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = mine;
  before.hand[currentPlayer][1] = copper;
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = silver;
  choice2 = 1;
  handPos = 0;
  playMine(&after, handPos, currentPlayer, choice1, choice2);
  printf("expected card in back of hand: %i, actual: %i\n",
    silver,
    after.hand[currentPlayer][after.handCount[currentPlayer] - 1]);

  printf("Trade Copper for Gold: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = mine;
  before.hand[currentPlayer][1] = copper;
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = gold;
  choice2 = 1;
  handPos = 0;
  result = playMine(&after, handPos, currentPlayer, choice1, choice2);
  printf("expected result: -1, actual: %i\n", result);
}
