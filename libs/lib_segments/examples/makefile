DESTDIR?=../..
PREFIX?=
#PATH_CC=../../../tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
#CC=$(PATH_CC)/arm-linux-gnueabihf-gcc

PATH_CC=../../../cross-pi-gcc-9.2.0-2/bin
CC=$(PATH_CC)/arm-linux-gnueabihf-gcc
LINK= -Xlinker -rpath-link=../../../cross-pi-gcc-9.2.0-2/arm-linux-gnueabihf/libc/lib

INC=-I$(DESTDIR)/include
LIB=-L$(DESTDIR)/lib

all:example

example : examples.c
	$(CC) $(INC) $(LIB) $(LINK) examples.c -o ../../../bin/segments -lwiringPI -lsegments
	scp ../../../bin/segments pi@192.168.1.46:~
	
clean : 
	rm -rf *.o
	rm -rf segments
	
