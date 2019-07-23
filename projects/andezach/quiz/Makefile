CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme:	clean
	gcc testme.c -o testme $(CFLAGS)
	./testme

coverage:
	gcov testme.c -b -f

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme
