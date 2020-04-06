DESTDIR?=..
PREFIX?=
PATH_CC=../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib

all:libMusic.a

libMusic.a : music.c
	$(CC) $(INC) $(LIB) -c  music.c -o music.o
	ar qvs ../lib/libMusic.a music.o

libMusic.so : music.c
	$(CC) $(INC) $(LIB) -shared -fPIC music.c -o ../lib/libMusic.so
	
clean: 
	rm -rf ../lib/libMusic.so
	rm -rf ../lib/libMusic.a
	rm -rf music.o
