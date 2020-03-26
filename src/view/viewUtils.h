#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 450

void SDL_ExitWithError(const char *message, const char *SDL_Error); 
int initSDLbasics(SDL_Window **window, SDL_Renderer **renderer, const char *windowTitle); 
int drawGameBoard(SDL_Renderer *renderer, SDL_Color color); 
int setGameBackground(SDL_Renderer *renderer); 