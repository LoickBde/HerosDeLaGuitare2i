DESTDIR?=../..
PREFIX?=
PATH_CC=../../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib

all:example

example : example.c
	$(CC) $(INC) $(LIB) example.c -o example -lwiringPI

clean : 
	rm -rf *.o
	rm -rf example
	
