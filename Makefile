CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lgmp
all: qs

qs: main.o sieve.o factor.o bigint.o
	$(CC) main.o sieve.o factor.o bigint.o -o qs $(LDFLAGS)

main.o: main.cc
	$(CC) main.cc $(CFLAGS)

sieve.o: sieve.cc
	$(CC) sieve.cc $(CFLAGS)

factor.o: factor.cc
	$(CC) factor.cc $(CFLAGS)

bigint.o: bigint.cc
	$(CC) bigint.cc $(CFLAGS)

clean: 
	rm -rf *.o qs
