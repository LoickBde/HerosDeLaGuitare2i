all: main.exe playArea.exe main_rpi.exe
ubuntu: main.exe playArea.exe
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
INC=-I$(DESTDIR)/include/SDL2
LIB=-L$(DESTDIR)/lib
OTHERS=-D_REENTRANT -lSDL2

main.exe: main.c
	gcc main.c $(CONF_OPT_UBU) -o main.exe
	mv main.exe ../../bin/

main_rpi.exe: main.c
	$(CC) $(INC) $(LIB) $(OTHERS) main.c -o main_rpi.exe
	mv main_rpi.exe ../../bin/

playArea.exe: playArea.c viewUtils.o
	gcc playArea.c viewUtils.o $(CONF_OPT_UBU) -o playArea.exe
	mv playArea.exe ../../bin/

viewUtils.o: viewUtils.c
	gcc -c viewUtils.c

clean: 
	rm -rf *.o 
	rm -f ../../bin/main.exe
	rm -f ../../bin/playArea.exe 
	rm -f ../../bin/main_rpi.exe