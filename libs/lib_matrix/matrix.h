#include "../include/header.h"
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define	SPI_CHANNEL	1 //deux channel 0 ou 1
#define	SPI_SPEED	1000000 //vitesse d'horloge du SPI

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

char good[] = {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};


char bad[] = {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};



void initSPI(void); //fonction d'initialisation du bus SPI

//Permet d'écrire data à l'adresse address sur le max
//Format (voir datasheet) : on un tableau de deux octet adress + data
void writeMatrix(char address, char data); 

//Fonction d'initialisation de la matrice
void initMatrix();

//Dessine la forme toDraw sur la matrice
void drawMatrix(char * toDraw);

//Fct de test
void drawTest();

void drawGood();

void drawBad();
