#include "../../include/header.h"

typedef struct cursor{
    SDL_Rect rect; 
    int position; //Position du curuseur sur l'écran (ou non)
} cursor; 


void SDL_ExitWithError(const char *message); 
void initSDLbasics(SDL_Window **window, SDL_Renderer **renderer, const char *windowTitle); 
SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path); 
void initTexturesGameBoard(SDL_Renderer *renderer, SDL_Texture **texture_foreground, SDL_Texture **texture_background, SDL_Texture **texture_gameBoard); 
void drawGameBoard(SDL_Renderer *renderer); 
void createGameBoard(SDL_Renderer *renderer, SDL_Texture *texture_foreground, SDL_Texture *texture_background, SDL_Texture **texture_gameBoard); 
void SDL_limitFPS(unsigned int limit); 