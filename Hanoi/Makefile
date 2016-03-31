.Phony: hanoi clean
string : hanoi.c ~/Pobrane/Pobrane/primlib/primlib.c
	gcc -g -D_REENTRANT -Wall -pedantic hanoi.c ~/Pobrane/Pobrane/primlib/primlib.c -o hanoi -lm -std=c99 -lSDL -lpthread -lSDL_gfx
clean: 
	rm -f hanoi
