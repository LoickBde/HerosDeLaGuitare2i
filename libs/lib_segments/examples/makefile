DESTDIR?=../..
PREFIX?=
PATH_CC=../../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib

all:7segments

7segments : 7segments.c
	$(CC) $(INC) $(LIB) 7segments.c -o 7segments -lwiringPI
clean : 
	rm -rf *.o
	rm -rf example
	rm -rf 7segments
	
