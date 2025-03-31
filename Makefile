CC = gcc
CFLAGS = -g -Wall -O3 -pedantic `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image
TARGET = game

OBJ = main.o sdl_utils.o game_object.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

main.o: main.c sdl_utils.h
	$(CC) $(CFLAGS) -c main.c

sdl_utils.o: sdl_utils.c sdl_utils.h
	$(CC) $(CFLAGS) -c sdl_utils.c

game_object.o: game_object.c game_object.h
	$(CC) $(CFLAGS) -c game_object.c
clean:
	rm -f $(TARGET) $(OBJ)
