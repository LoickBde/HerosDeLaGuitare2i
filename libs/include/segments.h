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


extern const uint8_t seg_numbers[]; //tableau des relations nombre / segments
int fd;

//Fonction d'init du bus I2C et du 7segments
void initSegments();
void turnOnSegments();
void turnOffSegments();
void test();
void writeScore(int score);
void writeSegment(int digit, int number);
