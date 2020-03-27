#include "../include/header.h"
#include <wiringPiI2C.h>

#define	SEG_ADDRESS         0x70 
#define SYS_SETUP_ADDRESS   0x20
#define ROW_INT_ADDRESS     0xA0
#define DISP_SETUP_ADDRESS  0x80


//Fonction d'init du bus SPI et du 7segments
void initSegments();
void turnOnSegments();
void turnOffSegments();

