#include <matrix.h>

char good[] = {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
char bad[] = {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};

char test[] = { 
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

void initSPI(){
	int fd;
	if((fd = wiringPiSPISetup(SPI_CHANNEL,SPI_SPEED)) == -1){
		perror("Erreur init SPI");
		exit(-1);	
	}
}

void writeMatrix(char address, char data){
	char dataToSend[2];
	dataToSend[0] = address;
	dataToSend[1] = data;
	//2 = nombre d'élements
	wiringPiSPIDataRW(SPI_CHANNEL,dataToSend,2);
}

void initMatrix(){

	initSPI(); // On init le bus SPI
	
	//Pas de décode mode (voir datasheet, adresse 0xX9) pour la matrice
	//Il faudra en mettre un pour les 7 segments aprés
	writeMatrix(0x09,0);
	
	//Intensité (adresse 0xXA) à la moitié (0x08, de 0 à F)
	writeMatrix(0x0A,0x08);

	//Scan limit (adresse 0xXB) = nb de digit utilisé, all = 7
	writeMatrix(0x0B,0x07);

	//Shutdown (adresse 0xXC), allumage de la matrice
	// 1 = On, 0 = OFF
	writeMatrix(0x0C,1);
}

//Adresse du digit 0 = 1
//	     digit 1 = 2 ...
void drawMatrix(char * toDraw){
	int i;
	for(i=0;i<8;i++){
		writeMatrix(i+1,*(toDraw+i));
	}
}

void drawTest(){
	drawMatrix(test);
}

void drawGood(){
	drawMatrix(good);
}
void drawBad(){
	drawMatrix(bad);
}
