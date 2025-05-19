
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
CFLAGS = -Wall -Wextra -std=c99 -g

# Your source files
SRCS = main.c sdl_utils.c game_object.c game_ui.c
OBJS = $(SRCS:.c=.o)

# Linker flags:
# -Llibs tells linker where to find .so files at link time
# -lSDL2 etc to link SDL2 libraries
# -Wl,-rpath,'$$ORIGIN/libs' tells loader to look for libs in libs/ at runtime
LDFLAGS = -Llibs -Wl,-rpath,'$$ORIGIN/libs' -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lpthread -ldl -lrt -lX11

TARGET = space_shooter

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
