DESTDIR?=..
PREFIX?=
PATH_CC=../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib

all:libSegments.a

libSegments.a : segments.c
	$(CC) $(INC) $(LIB) -c  segments.c -o segments.o
	ar qvs ../lib/libSegments.a segments.o

libSegments.so : segments.c
	$(CC) $(INC) $(LIB) -shared -fPIC segments.c -o ../lib/libSegments.so 

clean: 
	rm -rf ../lib/libSegments.so
	rm -rf ../lib/libSegments.a
	rm -rf segments.o

