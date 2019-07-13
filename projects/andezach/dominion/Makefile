CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c dominion.o rngs.o

	echo "Result for running Baron tests (unittest1.c):" > unittestresults.out
	echo >> unittestresults.out
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 baronEffect >> unittestresults.out
	echo >> unittestresults.out

	echo "Result for running Minion tests (unittest2.c):" >> unittestresults.out
	echo >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 minionEffect >> unittestresults.out
	echo >> unittestresults.out

	echo "Result for running Ambassador tests (unittest3.c):" >> unittestresults.out
	echo >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 ambassadorEffect >> unittestresults.out
	echo >> unittestresults.out

	echo "Result for running Tribute tests (unittest4.c):" >> unittestresults.out
	echo >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 tributeEffect >> unittestresults.out
	echo >> unittestresults.out

	echo "Result for running Mine tests (unittest5.c):" >> unittestresults.out
	echo >> unittestresults.out
	gcc -o unittest5 unittest5.c dominion.o rngs.o $(CFLAGS)
	./unittest5 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 mineEffect >> unittestresults.out
	echo >> unittestresults.out

	echo "Result for running initializeGame tests (cardtest1.c):" >> unittestresults.out
	echo >> unittestresults.out
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 initializeGame >> unittestresults.out
	echo >> unittestresults.out

	echo "Result for running shuffle tests (cardtest2.c):" >> unittestresults.out
	echo >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 shuffle >> unittestresults.out
	echo >> unittestresults.out

	echo "Result for running endTurn tests (cardtest3.c):" >> unittestresults.out
	echo >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 endTurn >> unittestresults.out
	echo >> unittestresults.out

	echo "Result for running getWinners tests (cardtest4.c):" >> unittestresults.out
	echo >> unittestresults.out
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 getWinners >> unittestresults.out
	echo >> unittestresults.out

	echo "Result for running drawCard tests (cardtest5.c):" >> unittestresults.out
	echo >> unittestresults.out
	gcc -o cardtest5 cardtest5.c dominion.o rngs.o $(CFLAGS)
	./cardtest5 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f | grep -A 5 drawCard >> unittestresults.out
	echo >> unittestresults.out

all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
