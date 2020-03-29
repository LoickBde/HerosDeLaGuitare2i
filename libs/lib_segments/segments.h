#include "../include/header.h"
#include <wiringPiI2C.h>

#define	SEG_ADDRESS         0x70 
#define SYS_SETUP_ADDRESS   0x20
#define ROW_INT_ADDRESS     0xA0
#define DISP_SETUP_ADDRESS  0x80

#define	DIGIT_1             0x00     
#define DIGIT_2             0x02
#define DIGIT_3             0x06
#define DIGIT_4             0x08

const uint8_t number[] = { 
	0x3F, /* 0 */ 
	0x06, /* 1 */ 
	0x5B, /* 2 */ 
	0x4F, /* 3 */ 
	0x66, /* 4 */ 
	0x6D, /* 5 */ 
	0x7D, /* 6 */ 
	0x07, /* 7 */ 
	0x7F, /* 8 */ 
	0x6F, /* 9 */ 
	0x77, /* a */ 
	0x7C, /* b */ 
	0x39, /* C */ 
	0x5E, /* d */ 
	0x79, /* E */ 
	0x71, /* F */ 
}; 

int fd;

//Fonction d'init du bus SPI et du 7segments
void initSegments();
void turnOnSegments();
void turnOffSegments();
void test();
void writeScore(int score);
void writeSegment(int digit, int number);
