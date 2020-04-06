#include "../include/header.h"
#include <wiringPiSPI.h>

#define	SPI_CHANNEL	1 //deux channel 0 ou 1
#define	SPI_SPEED	1000000 //vitesse d'horloge du SPI

extern char good[];

extern char bad[];

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

void turnOffMatrix();
