#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 450

void SDL_ExitWithError(const char *message); 
void initSDLbasics(SDL_Window **window, SDL_Renderer **renderer, const char *windowTitle); 
SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path); 
void drawGameBoard(SDL_Renderer *renderer); 
void setGameBoard(SDL_Renderer **renderer, SDL_Texture *texture_foreground, SDL_Texture *texture_background); 