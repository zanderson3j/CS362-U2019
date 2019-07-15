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
  struct gameState state;

  int result;

  printf("Successful Return from Function for Valid Inputs: ");
  memset(&state, 23, sizeof(struct gameState));
  result = initializeGame(numPlayer, k, seed, &state);
  printf("expected result: 0, actual: %i\n", result);

  printf("Number of Players is 2: ");
  printf("expected number of players: 2, actual: %i\n", state.numPlayers);

  printf("For 2 Players Supply Card Count Correct:\n");
  printf("card: expected, actual\n");
  printf("curse: 10, %i\n", state.supplyCount[curse]);
  printf("estate: 8, %i\n", state.supplyCount[estate]);
  printf("duchy: 8, %i\n", state.supplyCount[duchy]);
  printf("province: 8, %i\n", state.supplyCount[province]);
  printf("copper: 46, %i\n", state.supplyCount[copper]);
  printf("silver: 40, %i\n", state.supplyCount[silver]);
  printf("gold: 30, %i\n", state.supplyCount[gold]);
  printf("adventurer: 8, %i\n", state.supplyCount[adventurer]);
  printf("minion: 8, %i\n", state.supplyCount[minion]);
  printf("ambassador: 8, %i\n", state.supplyCount[ambassador]);
  printf("tribute: 8, %i\n", state.supplyCount[tribute]);
  printf("mine: 8, %i\n", state.supplyCount[mine]);
  printf("remodel: 8, %i\n", state.supplyCount[remodel]);
  printf("smithy: 8, %i\n", state.supplyCount[smithy]);
  printf("village: 8, %i\n", state.supplyCount[village]);
  printf("baron: 8, %i\n", state.supplyCount[baron]);
  printf("great_hall: 8, %i\n", state.supplyCount[great_hall]);

  printf("Unchosen Kingdom Card not in Supply: ");
  printf("feast: -1, %i\n", state.supplyCount[feast]);

  printf("Both Players Have Deck: ");
  printf("expected deck count p1 and p2: 5 and 10, %i and %i\n", state.deckCount[0], state.deckCount[1]);

  printf("First Player has 5 Cards in Hand, Other Player has 0: ");
  printf("expected deck count for p1 and p2: 5 and 0, actual: %i and %i\n", state.handCount[0], state.handCount[1]);

  printf("Number of Players is 3: ");
  numPlayer = 3;
  memset(&state, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &state);
  printf("expected number of players: 3, actual: %i\n", state.numPlayers);

  printf("For 3 Players Supply Card Count Correct:\n");
  printf("card: expected, actual\n");
  printf("curse: 20, %i\n", state.supplyCount[curse]);
  printf("estate: 12, %i\n", state.supplyCount[estate]);
  printf("duchy: 12, %i\n", state.supplyCount[duchy]);
  printf("province: 12, %i\n", state.supplyCount[province]);
  printf("copper: 39, %i\n", state.supplyCount[copper]);
  printf("silver: 40, %i\n", state.supplyCount[silver]);
  printf("gold: 30, %i\n", state.supplyCount[gold]);
  printf("adventurer: 12, %i\n", state.supplyCount[adventurer]);
  printf("minion: 12, %i\n", state.supplyCount[minion]);
  printf("ambassador: 12, %i\n", state.supplyCount[ambassador]);
  printf("tribute: 12, %i\n", state.supplyCount[tribute]);
  printf("mine: 12, %i\n", state.supplyCount[mine]);
  printf("remodel: 12, %i\n", state.supplyCount[remodel]);
  printf("smithy: 12, %i\n", state.supplyCount[smithy]);
  printf("village: 12, %i\n", state.supplyCount[village]);
  printf("baron: 12, %i\n", state.supplyCount[baron]);
  printf("great_hall: 12, %i\n", state.supplyCount[great_hall]);

  printf("Duplicate Kingdom Card Request is Illegal: ");
  k[0] = tribute;
  memset(&state, 23, sizeof(struct gameState));
  result = initializeGame(numPlayer, k, seed, &state);
  printf("expected result: -1, actual: %i\n", result);
  k[0] = adventurer;

  printf("Can't Have More Than Max Players (4): ");
  numPlayer = 5;
  memset(&state, 23, sizeof(struct gameState));
  result = initializeGame(numPlayer, k, seed, &state);
  printf("expected result: -1, actual: %i\n", result);
}
