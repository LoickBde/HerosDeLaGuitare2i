all: main.exe 

#Options de compilation pour compiler SDL2
#$(sdl2-config --cflags --libs) = -I/usr/include/SDL2 -D_REENTRANT -lSDL2
CONF_OPT_UBU = -I/usr/include/SDL2 -D_REENTRANT -lSDL2

main.exe: main.c
	gcc -Wall -Wextra -L.\lib -I.\include ./main.c -o main.exe -lSDL2main -lSDL2 -lSDL2_ttf
	mv main.exe ../../bin/

clean: 
	rm -rf *.o 
	rm -f ../../bin/main.exe