CC = gcc
CFLAGS = -g -Wall -O3 -pedantic `sdl2-config --cflags` 
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm
TARGET = game
OBJ = main.o sdl_utils.o game_object.o game_ui.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
