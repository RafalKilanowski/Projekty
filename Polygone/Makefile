.Phony: polygone clean
string : polygone.c ~/Pobrane/primlib/primlib.c
	gcc -D_REENTRANT polygone.c ~/Pobrane/primlib/primlib.c -o polygone -lm -lSDL -lpthread -lSDL_gfx
clean: 
	rm -f polygone
