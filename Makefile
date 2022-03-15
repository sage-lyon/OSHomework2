CC=gcc
CFLAGS=-I. -pthread

all: fork-join rendezvous barrier

fork-join: fork-join.c
	$(CC) -o $@ $^ $(CFLAGS) 

rendezvous: rendezvous.c
	$(CC) -o $@ $^ $(CFLAGS)

barrier: barrier.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f fork-join rendezvous barrier
