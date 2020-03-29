DESTDIR?=../..
PREFIX?=
PATH_CC=../../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib

all:example

example : examples.c
	$(CC) $(INC) $(LIB) examples.c -o example -lwiringPI
	scp example pi@192.168.1.46:~
	
clean : 
	rm -rf *.o
	rm -rf example
	rm -rf 7segments
	rm -rf example
	
