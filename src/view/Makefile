all: main.exe 

#Options de compilation pour compiler SDL2
#$(sdl2-config --cflags --libs) = -I/usr/include/SDL2 -D_REENTRANT -lSDL2
CONF_OPT_UBU = -I/usr/include/SDL2 -D_REENTRANT -lSDL2

main.exe: main.c
	gcc main.c $(CONF_OPT_UBU) -o main.exe
	mv main.exe ../../bin/

clean: 
	rm -rf *.o 
	rm -f ../../bin/main.exe