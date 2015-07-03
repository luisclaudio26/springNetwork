CC=gcc
CFLAGS=-std=c99 -w -g
LIB=-lSDL -lm
SRC=src
INC=include
OBJ=temp

main: $(OBJ)/main.o $(OBJ)/grafx.o $(OBJ)/springNetwork.o $(OBJ)/particle.o
	$(CC) $(CFLAGS) $(LIB) -o main $(OBJ)/main.o $(OBJ)/grafx.o $(OBJ)/springNetwork.o $(OBJ)/particle.o

$(OBJ)/main.o: main.c
	$(CC) $(CFLAGS) $(LIB) -c main.c -o $(OBJ)/main.o

$(OBJ)/grafx.o: $(SRC)/grafx.c
	$(CC) $(CFLAGS) $(LIB) -c $(SRC)/grafx.c -o $(OBJ)/grafx.o

$(OBJ)/particle.o: $(SRC)/particle.c
	$(CC) $(CFLAGS) $(LIB) -c $(SRC)/particle.c -o $(OBJ)/particle.o

$(OBJ)/springNetwork.o: $(SRC)/springNetwork.c
	$(CC) $(CFLAGS) $(LIB) -c $(SRC)/springNetwork.c -o $(OBJ)/springNetwork.o