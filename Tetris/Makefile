.Phony: tetris clean
all : tetris.c ~/Pobrane/Pobrane/primlib/primlib.c
	gcc -fsanitize=address -std=gnu99 -D_REENTRANT -Wall -pedantic tetris.c ~/Pobrane/Pobrane/primlib/primlib.c -o tetris -lm -lSDL -lpthread -lSDL_gfx
clean: 
	rm -f tetris
