CC = gcc
CFLAGS = -g -Wall -O3 -pedantic `sdl2-config --cflags` 
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm
TARGET = game.exe
OBJ = main.o sdl_utils.o game_object.o game_ui.o

DLL_DIR = external_dlls

COPY_DLLS = cp $(DLL_DIR)/*.dll .

all: $(TARGET) copy-dlls

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


copy-dlls:
	cp $(DLL_DIR)/*.dll .

clean:
	rm -f $(TARGET) $(OBJ)    
