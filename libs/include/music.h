#include "../include/header.h"
#include <softTone.h>

#define BUZZER_PIN 1

typedef enum Note{
    DO = 262,
    REb = 277,
    RE = 294,
    MIb = 311,
    MI = 330,
    FA = 349,
    SOLb = 370,
    SOL = 392,
    LAb = 415,
    LA = 440,
    SIb = 466,
    SI = 494, 
} Note;

typedef enum Rythme{
    RONDE = 400,
    BLANCHEP = 300,
    BLANCHE = 200, //BLANCHE = 2 temps = 200% le temps unitaire
    NOIRE = 100, //Noire = 1 temps = 100%
    CROCHE = 50, //Croche = 50% d'un temps unitaire
    DOUBLE_CROCHE = 25 //Double croche = 1/4 de temps = 25% du temps unitaire
} Rythme;

int time; //La durée d'un temps dans une mesure (= 60/bpm ms)

void initMusic();
void setBPM(int bpm);
void playNote(Note note, Rythme rythme);
void playScale();
