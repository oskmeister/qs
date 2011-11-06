CC=gcc
CFLAGS=-c -std=gnu99 -Wall
LDFLAGS=-lgmp
all: qs
qs: main.o
	$(CC) $(LDFLAGS) main.o -o qs
main.o: main.c
	$(CC) $(CFLAGS) main.c
clean: 
	rm -rf *.o qs
