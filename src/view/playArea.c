#include "viewUtils.h" 

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("Erreur init SDL2");
    }
    window = SDL_CreateWindow(
                                "Zone de jeu !", 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED,
                                WIDTH, 
                                HEIGHT, 
                                SDL_WINDOW_SHOWN
                            );
    if(NULL == window)
    {
        SDL_ExitWithError("Erreur création fenêtre");
    }
     
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}