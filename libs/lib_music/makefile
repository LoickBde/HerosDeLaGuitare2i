DESTDIR?=..
PREFIX?=
#PATH_CC=../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
#CC=$(PATH_CC)/arm-linux-gnueabihf-gcc
PATH_CC=../../cross-pi-gcc-9.2.0-2/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

LINK= -Xlinker -rpath-link=../../cross-pi-gcc-9.2.0-2/arm-linux-gnueabihf/libc/lib

INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib

all:libMusic.a

libMusic.a : music.c
	$(CC) $(INC) $(LIB) $(LINK) -c  music.c -o music.o
	ar qvs ../lib/libMusic.a music.o

libMusic.so : music.c
	$(CC) $(INC) $(LIB) $(LINK) -shared -fPIC music.c -o ../lib/libMusic.so
	
clean: 
	rm -rf ../lib/libMusic.so
	rm -rf ../lib/libMusic.a
	rm -rf music.o
