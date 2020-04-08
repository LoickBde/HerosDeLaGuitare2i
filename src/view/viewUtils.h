#include "../../include/header.h"
#include <music.h>
#include <segments.h>
#include <matrix.h>

int stringPosition[NB_STRING]; 
int score; 

void SDL_ExitWithError(const char *message); 
void initSDLbasics(SDL_Window **window, SDL_Renderer **renderer, const char *windowTitle); 
SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path); 
void initTexturesGameBoard(SDL_Renderer *renderer, SDL_Texture **texture_foreground, SDL_Texture **texture_background, SDL_Texture **texture_gameBoard); 
void drawGameBoard(SDL_Renderer *renderer); 
void createGameBoard(SDL_Renderer *renderer, SDL_Texture *texture_foreground, SDL_Texture *texture_background, SDL_Texture **texture_gameBoard); 
void createMusicNote(SDL_Renderer *renderer, SDL_Texture **texture_musicNote); 
void SDL_limitFPS(unsigned int limit); 
void initNotesTest(SDL_Rect myRects[]); 
void initNotesFromFile(const char* path, SDL_Rect myRects[]); 
void animation(SDL_Renderer *renderer, SDL_Texture *texture_gameBoard, SDL_Texture *texture_musicNote, SDL_Rect myRects[], SDL_bool *songFinished); 
void checkNoteArea(int cooX, SDL_Rect myRects[]); 
void updateScore(int points); 