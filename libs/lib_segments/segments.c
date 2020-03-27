#include "segments.h"

void initSegments(){
    int fd;
    // CHECK(wiringPiI2CSetup(SEG_ADDRESS),"Erreur init bus I2C"); //Init bus I2C
    if((fd = wiringPiI2CSetup(SEG_ADDRESS)) == -1){
        perror("Erreur inir MK");
        exit(-1);
    }
    CHECK(wiringPiI2CWriteReg8(fd, SYS_SETUP_ADDRESS, 0b00100001),"Erreur init MK"); //Normal operation mode 
    CHECK(wiringPiI2CWriteReg8(fd, ROW_INT_ADDRESS, 0b10100011),"Erreur config Int mode"); //Int mode 
    CHECK(wiringPiI2CWriteReg8(fd, DISP_SETUP_ADDRESS, 0b10000000),"Erreur config blink and disp"); //Blinking off + display off
}

void turnOnSegments(){
    CHECK(wiringPiI2CWriteReg8(SEG_ADDRESS, DISP_SETUP_ADDRESS, 0b10000001),"Erreur config blink and disp"); //Blinking off + display on
}

void turnOffSegments(){
    CHECK(wiringPiI2CWriteReg8(SEG_ADDRESS, DISP_SETUP_ADDRESS, 0b10000000),"Erreur config blink and disp"); //Blinking off + display on
    CHECK(wiringPiI2CWriteReg8(SEG_ADDRESS, SYS_SETUP_ADDRESS, 0b00100000),"Erreur init MK"); //Standby mode
}

