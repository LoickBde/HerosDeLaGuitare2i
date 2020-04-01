#include "../../include/header.h"

void SDL_ExitWithError(const char *message); 
void initSDLbasics(SDL_Window **window, SDL_Renderer **renderer, const char *windowTitle); 
SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path); 
void initTexturesGameBoard(SDL_Renderer *renderer, SDL_Texture **texture_foreground, SDL_Texture **texture_background, SDL_Texture **texture_gameBoard); 
void drawGameBoard(SDL_Renderer *renderer); 
void createGameBoard(SDL_Renderer *renderer, SDL_Texture *texture_foreground, SDL_Texture *texture_background, SDL_Texture **texture_gameBoard); 
void createMusicNote(SDL_Renderer *renderer, SDL_Texture **texture_musicNote); 
void SDL_limitFPS(unsigned int limit); 