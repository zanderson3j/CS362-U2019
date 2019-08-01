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
  int choice1, choice2;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  int result;

  //Test for choice of 2 coins.
  printf("Get 2 Coins: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = minion; //put minion card in hand
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 1;
  choice2 = 0;
  minionEffect(currentPlayer, choice1, choice2, &after, 0);
  printf("expected coins: %i, actual: %i\n", before.coins + 2, after.coins);

  //Test the number of actions increases by one.
  printf("Increase Actions by One: ");
  printf("expected numActions: %i, actual: %i\n", before.numActions + 1, after.numActions);

  //Test current player has 4 cards in hand after starting with 5.
  printf("Current Player Draws New Hand: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = minion; //put minion card in hand
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 0;
  choice2 = 1;
  minionEffect(currentPlayer, choice1, choice2, &after, 0);
  printf("expected hand count: 4, actual: %i\n", after.handCount[currentPlayer]);

  //Test other player less than 5 cards in hand doesnt draw any.
  printf("Other Player with Less than 5 Cards Doesn't Draw New Hand: ");
  printf("expected handCount: %i, actual: %i\n", before.handCount[1], after.handCount[1]);

  //Test other player with 5 cards in hand now has 4 cards in hand from drawing.
  printf("Other Player with 5 Cards Draws New Hand: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = minion; //put minion card in hand
  for(int i = 0; i < 5; ++i) {
    gainCard(estate, &before, 2, currentPlayer + 1);
  }
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 0;
  choice2 = 1;
  minionEffect(currentPlayer, choice1, choice2, &after, 0);
  printf("expected hand count: 4, actual: %i\n", after.handCount[currentPlayer + 1]);

  //Test making two choices is illegal
  printf("Making two choices is illegal: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.hand[currentPlayer][0] = minion; //put minion card in hand
  memcpy(&after, &before, sizeof(struct gameState));
  choice1 = 1;
  choice2 = 1;
  result = minionEffect(currentPlayer, choice1, choice2, &after, 0);
  printf("expected result: -1, actual: %i\n", result);

}
