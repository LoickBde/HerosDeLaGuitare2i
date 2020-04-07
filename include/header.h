#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 450
#define SIZE_SIDE 150
#define SIZE_BOT 80
#define NB_STRING 4
#define NB_NOTE_STRING 2 
#define NB_NOTE 8 //NB_STRING * NB_NOTE_STRING
#define MUSIC_NOTE_SIZE 25
#define SPEED_MOVEMENT 2
#define FPS 30
#define FPS_LIMIT 1000/30
#define MAX_BUFF 255