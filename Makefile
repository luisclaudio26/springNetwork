CC=gcc
CFLAGS=-std=c99 -w -g
LIB=-lSDL -lm
SRC=src
INC=include

main: main.o grafx.o springNetwork.o particle.o
	$(CC) $(CFLAGS) $(LIB) -o main main.o grafx.o springNetwork.o particle.o

main.o: main.c
	$(CC) $(CFLAGS) $(LIB) -c main.c -o main.o

grafx.o: $(SRC)/grafx.c
	$(CC) $(CFLAGS) $(LIB) -c $(SRC)/grafx.c -o grafx.o

particle.o: $(SRC)/particle.c
	$(CC) $(CFLAGS) $(LIB) -c $(SRC)/particle.c -o particle.o

springNetwork.o: $(SRC)/springNetwork.c
	$(CC) $(CFLAGS) $(LIB) -c $(SRC)/springNetwork.c -o springNetwork.o

clean:
	rm *.o