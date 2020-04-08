all: main.exe main_rpi.exe
ubuntu: main.exe
rpi: main_rpi.exe

#Options de compilation pour compiler SDL2
#$(sdl2-config --cflags --libs) = -I/usr/include/SDL2 -D_REENTRANT -lSDL2
#CONF_OPT_UBU = -I/usr/include/SDL2 -D_REENTRANT -lSDL2
CONF_OPT_UBU=`sdl2-config --cflags --libs` 

#Export du chemin du compilateur croisé de la rpi
PATH_CC=../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

#Définitions du chemin des include et lib pour sdl2 sur rpi
DESTDIR=../../libs
INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib
OPT=-D_REENTRANT -lSDL2

main.exe: main.c playArea.o viewUtils.o
	gcc -Wall -Wextra -L.\lib -I.\include ./main.c playArea.o viewUtils.o -o ../../bin/main.exe -lSDL2main -lSDL2 -lSDL2_ttf

main_rpi.exe: main.c playAreaRpi.o viewUtilsRpi.o
	$(CC) $(INC) $(LIB) -D_RPI-Wall -Wextra main.c playArea.o viewUtils.o -o ../../bin/main_rpi.exe -lSDL2main -lSDL2 -lSDL2_ttf -lmatrix -lsegments -lmusic

playArea.o: playArea.c
	gcc playArea.c $(CONF_OPT_UBU) -c

playAreaRpi.o: playArea.c 
	$(CC) $(INC) $(LIB) -D_RPI playArea.c $(OPT) -c

viewUtils.o: viewUtils.c
	gcc viewUtils.c -c

viewUtilsRpi.o: viewUtils.c
	$(CC) $(INC) $(LIB) $(OPT) -D_RPI viewUtils.c -c

clean: 
	rm -rf *.o 
	rm -f ../../bin/main.exe
	rm -f ../../bin/playArea.exe 
	rm -f ../../bin/main_rpi.exe