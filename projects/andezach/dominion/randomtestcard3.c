#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int printFailure(char *message, int currentPlayer, int nextPlayer, struct gameState *before, struct gameState *after, int result) {
  printf("%s: currentPlayer-%i, nextPlayer-%i, nxtDiscardCt-%i, nxtDeckCt-%i, coins-%i->%i, handCt-%i->%i, numActions-%i->%i, result-%i\n",
            message,
            currentPlayer,
            nextPlayer,
            before->discardCount[nextPlayer],
            before->deckCount[nextPlayer],
            before->coins,
            after->coins,
            before->handCount[currentPlayer],
            after->handCount[currentPlayer],
            before->numActions,
            after->numActions,
            result);
  return 1;
}

int testResults(int currentPlayer, int nextPlayer, struct gameState *before, struct gameState *after, int *tributeRevealedCards, int result) {
  if (result == 0) {
    if ((before->discardCount[nextPlayer] + before->deckCount[nextPlayer]) <= 1) {
      if (before->deckCount[nextPlayer] > 0) {
        if(tributeRevealedCards[0] != before->deck[nextPlayer][before->deckCount[nextPlayer]-1]) {
          return printFailure("Last card in deck not tributed", currentPlayer, nextPlayer, before, after, result);
        }
        if(before->deckCount - 1 != after->deckCount) {
          return printFailure("Card not removed from deck", currentPlayer, nextPlayer, before, after, result);
        }
      } else if (before->discardCount[nextPlayer] > 0) {
        if(tributeRevealedCards[0] != before->discard[nextPlayer][before->discardCount[nextPlayer]-1]) {
          return printFailure("Last discard not tributed", currentPlayer, nextPlayer, before, after, result);
        }
        if(before->discardCount - 1 != after->discardCount) {
          return printFailure("Card not removed from discard", currentPlayer, nextPlayer, before, after, result);
        }
      }
    }

    else {
      for(int i = 0; i < 2; i++) {
        if (tributeRevealedCards[i] != before->deck[nextPlayer][before->deckCount[nextPlayer]-1-i]
          && tributeRevealedCards[i] != -1) {
          return printFailure("Didn't get tribute cards", currentPlayer, nextPlayer, before, after, result);
        }
      }
    }

    for (int i = 0; i < 2; i++) {
      if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver
        || tributeRevealedCards[i] == gold) {  //Treasure cards
        if (after->coins <= before->coins) {
          return printFailure("Treasure card didn't inc coins", currentPlayer, nextPlayer, before, after, result);
        }
      }

      else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy
        || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens
        || tributeRevealedCards[i] == great_hall) {  //Victory Card Found
        if (after->handCount[currentPlayer] < before->handCount[currentPlayer]) {
          return printFailure("Victory card didn't inc hand", currentPlayer, nextPlayer, before, after, result);
        }
      }

      else {
        if (after->numActions <= before->numActions + 2) {
          return printFailure("Action card didn't inc actions", currentPlayer, nextPlayer, before, after, result);
        }
      }
    }
  }
  return 0;
}

int main() {

  const int numOfTests = 2000;
  int currentPlayer = 0;
  int nextPlayer = 1;
  int tributeRevealedCards[3];
  int result;
  int failed = 0;
  int k[10] = {adventurer, minion, ambassador, tribute, mine, remodel, smithy, village, baron, great_hall};
  struct gameState before, after;

  srand(time(0));

  for (int i = 0; i < numOfTests; ++i) {
    memset(&before, 23, sizeof(struct gameState));
    initializeGame(2, k, rand(), &before);
    before.discardCount[nextPlayer] = rand() % 6;
    before.deckCount[nextPlayer] = rand() % 6;
    for (int j = 0; j < before.discardCount[nextPlayer]; ++j) {
      before.discard[nextPlayer][j] = rand() % 27;
    }
    for (int j = 0; j < before.deckCount[nextPlayer]; ++j) {
      before.deck[nextPlayer][j] = rand() % 27;
    }
    memcpy(&after, &before, sizeof(struct gameState));
    result = tributeEffect(currentPlayer, nextPlayer, &after, tributeRevealedCards);
    failed += testResults(currentPlayer, nextPlayer, &before, &after, tributeRevealedCards, result);
  }

  printf("Failed %i out of %i.", failed, numOfTests);

  return 0;
}
