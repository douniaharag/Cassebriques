CC=gcc
CFLAGS=-W -Wall -g
LDFLAGS=
EXEC=casseBriques

all: $(EXEC)

casseBriques: casseBriques.o main.o
	$(CC) -o casseBriques casseBriques.o main.o $(LDFLAGS)

casseBriques.o: casseBriques.c
	$(CC) -o casseBriques.o -c casseBriques.c $(CFLAGS)

main.o: main.c casseBriques.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)