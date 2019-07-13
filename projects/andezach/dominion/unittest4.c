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
  int nextPlayer = 1;
  int tributeRevealedCards[3];
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  printf("Next Player Has Top Two Cards Discarded: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.deck[nextPlayer][before.deckCount[nextPlayer] - 3] = estate;
  memcpy(&after, &before, sizeof(struct gameState));
  tributeEffect(currentPlayer, nextPlayer, &after, tributeRevealedCards);
  printf("expected handCount and top card: %i:%i, actual: %i:%i\n", before.deckCount[nextPlayer] - 2, estate, after.deckCount[nextPlayer], after.deck[nextPlayer][after.deckCount[nextPlayer] - 1]);

  printf("Action Card Adds 2 Actions to Turn: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.deck[nextPlayer][before.deckCount[nextPlayer] - 1] = minion;
  before.deck[nextPlayer][before.deckCount[nextPlayer] - 2] = copper;
  memcpy(&after, &before, sizeof(struct gameState));
  tributeEffect(currentPlayer, nextPlayer, &after, tributeRevealedCards);
  printf("expected actions: %i, actual: %i\n", before.numActions + 2, after.numActions);

  printf("Treasue Card Adds 2 Coins to Player: ");
  printf("expected coins: %i, actual: %i\n", before.coins + 2, after.coins);

  printf("Victory Card Adds 2 Cards to Player's Hand: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.deck[nextPlayer][before.deckCount[nextPlayer] - 1] = province;
  before.deck[nextPlayer][before.deckCount[nextPlayer] - 2] = copper;
  memcpy(&after, &before, sizeof(struct gameState));
  tributeEffect(currentPlayer, nextPlayer, &after, tributeRevealedCards);
  printf("expected handCount: %i, actual: %i\n", before.handCount[currentPlayer] + 2, after.handCount[currentPlayer]);

  printf("Duplicate Cards Have One Reward: ");
  memset(&before, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &before);
  before.deck[nextPlayer][before.deckCount[nextPlayer] - 1] = copper;
  before.deck[nextPlayer][before.deckCount[nextPlayer] - 2] = copper;
  memcpy(&after, &before, sizeof(struct gameState));
  tributeEffect(currentPlayer, nextPlayer, &after, tributeRevealedCards);
  printf("expected coins: %i, actual: %i\n", before.coins + 2, after.coins);
}
