CC = gcc
OUTPUT = ca
SRC = ca.c
CFLAGS = --std=c99

ca: Makefile $(SRC)
	$(CC) -o $(OUTPUT) $(SRC) $(CFLAGS)
