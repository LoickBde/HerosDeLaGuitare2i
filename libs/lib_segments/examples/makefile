DESTDIR?=../..
PREFIX?=
PATH_CC=../../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib

all:example

example : examples.c
	$(CC) $(INC) $(LIB) examples.c -o ../../../bin/segments -lwiringPI -lsegments
	scp ../../../bin/segments pi@192.168.1.46:~/HerosDeLaGuitare2i/examples/
	
clean : 
	rm -rf *.o
	rm -rf segments
	
