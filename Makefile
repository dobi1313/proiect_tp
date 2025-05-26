#CC = gcc
#CFLAGS = -g -Wall -O3 -pedantic `sdl2-config --cflags` 
#LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm
#TARGET = game.exe
#OBJ = main.o sdl_utils.o game_object.o game_ui.o

#all: $(TARGET)

#$(TARGET): $(OBJ)
#	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@

#clean:
#	rm -f $(TARGET) $(OBJ)

CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -Llibs -Wl,-rpath,'$$ORIGIN/libs' -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lpthread -ldl -lrt -lX11

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
BIN = space_shooter

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f space_shooter

