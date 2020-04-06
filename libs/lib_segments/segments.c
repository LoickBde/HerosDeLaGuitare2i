#include <segments.h>

const uint8_t seg_numbers[] = { 
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

void initSegments(){
    // CHECK(wiringPiI2CSetup(SEG_ADDRESS),"Erreur init bus I2C"); //Init bus I2C
    if((fd = wiringPiI2CSetup(SEG_ADDRESS)) == -1){
        perror("Erreur inir MK");
        exit(-1);
    }
    CHECK(wiringPiI2CWrite(fd, SYS_SETUP_ADDRESS | 1),"Erreur init MK"); //Normal operation mode / Oscillator on
    CHECK(wiringPiI2CWrite(fd, DISP_SETUP_ADDRESS | 1),"Erreur config blink and disp"); //Blinking off + display on
    CHECK(wiringPiI2CWrite(fd, 0xE0 | 15),"Erreur config brightness"); //Brightness max
}

void turnOnSegments(){
    CHECK(wiringPiI2CWrite(fd, DISP_SETUP_ADDRESS | 1),"Erreur config blink and disp"); //Blinking off + display on
}

void turnOffSegments(){
    CHECK(wiringPiI2CWrite(fd, DISP_SETUP_ADDRESS | 0b10000000),"Erreur config blink and disp"); //Blinking off + display off
    CHECK(wiringPiI2CWrite(fd, SYS_SETUP_ADDRESS | 0b00100000),"Erreur init MK"); //Standby mode
}

void test(){
    CHECK(wiringPiI2CWriteReg8(fd, 0x00, seg_numbers[10]),"Erreur disp"); //Blinking off + display on 
    CHECK(wiringPiI2CWriteReg8(fd, 0x02, seg_numbers[5]),"Erreur disp"); //Blinking off + display on 
    CHECK(wiringPiI2CWriteReg8(fd, 0x06, seg_numbers[5]),"Erreur disp"); //Blinking off + display on
    CHECK(wiringPiI2CWriteReg8(fd, 0x08, 0),"Erreur disp"); //Blinking off + display on
}

void writeScore(int score){
    int m=(score-score%1000)/1000;
    int c=(score%1000-score%100)/100;
    int d=(score%100-score%10)/10;
    int u=score%10; 

    writeSegment(DIGIT_1, m);
    writeSegment(DIGIT_2, c);
    writeSegment(DIGIT_3, d);
    writeSegment(DIGIT_4, u);
}

void writeSegment(int digit, int num){
    CHECK(wiringPiI2CWriteReg8(fd, digit, seg_numbers[num]),"Erreur disp"); //Blinking off + display on 
}



