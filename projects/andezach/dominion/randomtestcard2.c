#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() {

  const int numOfTests = 2000;
  int currentPlayer;
  int choice1;
  int choice2;
  int handPos;
  int result;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  srand(time(0));

  for (int i = 0; i < numOfTests; ++i) {
    currentPlayer = rand() % 2; //2 players
    result = minionEffect(currentPlayer, choice1, choice2, &after, handPos);
  }

  return 0;
}
