CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=-lgmp -lgmpxx -O2
all: qs

qs: main.o sieve.o factor.o 
	$(CC) main.o sieve.o factor.o -o qs $(LDFLAGS)

main.o: main.cc
	$(CC) main.cc $(CFLAGS)

sieve.o: sieve.cc
	$(CC) sieve.cc $(CFLAGS)

factor.o: factor.cc
	$(CC) factor.cc $(CFLAGS)

clean: 
	rm -rf *.o qs
