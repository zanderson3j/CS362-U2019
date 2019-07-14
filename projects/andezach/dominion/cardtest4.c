#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
  int seed = 1000;
  int numPlayer = 2;
  int players[MAX_PLAYERS];
  int p1 = 0;
  int p2 = 1;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState state;

  printf("Player With Highest Score is Winner, Others are Losers: ");
  memset(&state, 23, sizeof(struct gameState));
  initializeGame(numPlayer, k, seed, &state);
  //Makes controlling score easier if only count up the cards in the hand.
  state.discardCount[p1] = 0;
  state.discardCount[p2] = 0;
  state.deckCount[p1] = 0;
  state.deckCount[p2] = 0;
  state.handCount[p1] = 1;
  state.handCount[p2] = 1;
  state.hand[p1][0] = province;
  state.hand[p2][0] = estate;
  getWinners(players, &state);
  printf("expected winner loser: p1 - 1, p2 - 0, actual: p1 - %i, p2 - %i\n", players[0], players[1]);

  printf("Player Gets Extra Points for Less Turns: ");
  state.hand[p1][0] = province;
  state.hand[p2][0] = province;
  getWinners(players, &state);
  printf("expected winner loser: p1 - 0, p2 - 1, actual: p1 - %i, p2 - %i\n", players[0], players[1]);

  printf("Tie Means Both Players Win: ");
  endTurn(&state);
  state.discardCount[p1] = 0;
  state.discardCount[p2] = 0;
  state.deckCount[p1] = 0;
  state.deckCount[p2] = 0;
  state.handCount[p1] = 1;
  state.handCount[p2] = 1;
  state.hand[p1][0] = province;
  state.hand[p2][0] = province;
  getWinners(players, &state);
  printf("expected winner loser: p1 - 1, p2 - 1, actual: p1 - %i, p2 - %i\n", players[0], players[1]);
}
