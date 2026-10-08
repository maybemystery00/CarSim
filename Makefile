CC = gcc
CFLAGS = -Iinclude

SRC = src/main.c src/simulation.c src/car.c

carsim.exe: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o carsim.exe