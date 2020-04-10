DESTDIR?=..
PREFIX?=
#PATH_CC=../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
#CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

PATH_CC=../../cross-pi-gcc-9.2.0-2/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc
LINK= -Xlinker -rpath-link=../../cross-pi-gcc-9.2.0-2/arm-linux-gnueabihf/libc/lib

INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib

all: libMatrix.a

libMatrix.a : matrix.c
	$(CC) $(INC) $(LIB) $(LINK) -c  matrix.c -o matrix.o
	ar qvs ../lib/libMatrix.a matrix.o

libMatrix.so : matrix.c
	$(CC) $(INC) $(LIB) $(LINK) -shared -fPIC matrix.c -o ../lib/libMatrix.so
	
clean: 
	rm -rf ../lib/libMatrix.so
	rm -rf ../lib/libMatrix.a
	rm -rf matrix.o

