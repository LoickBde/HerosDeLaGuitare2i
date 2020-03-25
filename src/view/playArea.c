#include "viewUtils.h" 

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL; 
    SDL_Color Color_BlueGrey = {79,109,122,1}; 

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Erreur init SDL2");
    

    window = SDL_CreateWindow(
                                "Zone de jeu !", 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED,
                                WIDTH, 
                                HEIGHT, 
                                SDL_WINDOW_SHOWN
                            );
    if(window == NULL)
        SDL_ExitWithError("Erreur création fenêtre");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
    if(renderer == NULL)
        SDL_ExitWithError("Erreur création renderer");

   // SDL_Delay(1000); //Pause 

    if(initGameBoard(renderer, Color_BlueGrey) != 0)
        SDL_ExitWithError("Erreur init plateau de jeu");

    SDL_Delay(5000); //Pause 

    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}