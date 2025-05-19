
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

# Path to your local shared libraries
LIBDIR = libs

# Linker flags:
# -L to find libs at link time
# -l to link specific libs
# -Wl,-rpath sets runtime search path to libs/
LDFLAGS = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR) \
          -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lpthread -ldl -lrt -lX11

TARGET = space_shooter
SRCS = main.c sdl_utils.c game_object.c game_ui.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)