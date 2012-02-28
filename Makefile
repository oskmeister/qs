CC=gcc
CFLAGS=-c -std=gnu99 -Wall
LDFLAGS=-lgmp
all: qs
qs: main.o sieve.o
	$(CC) main.o sieve.o -o qs $(LDFLAGS)
main.o: main.c
	$(CC) main.c $(CFLAGS)
sieve.o: sieve.c
	$(CC) sieve.c $(CFLAGS)
clean: 
	rm -rf *.o qs
