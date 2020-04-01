#include "viewUtils.h" 

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; //Pointeur sur la fenêtre
    SDL_Renderer *renderer = NULL; //Pointeur sur le renderer
    SDL_Texture *texture_foreground, *texture_background, *texture_gameBoard = NULL; //Texture pour les cordes, l'image de fond et les deux en un
    SDL_Texture *texture_cursor; //Texture contenant le curseur a déssiner
    SDL_bool prgm_running = SDL_TRUE; 

    initSDLbasics(&window, &renderer, "Zone de jeu"); //Initialise les bases de la sdl (fenetre, renderer)

    initTexturesGameBoard(renderer, &texture_foreground, &texture_background, &texture_gameBoard); 
    
    createGameBoard(renderer, texture_foreground, texture_background, &texture_gameBoard); //Mise en place de la zone de jeu
    
    SDL_RenderPresent(renderer); //Maj de l'affichage 
    
    SDL_DestroyTexture(texture_foreground); //Détruit les textures qui ne servent plus
    SDL_DestroyTexture(texture_background); 


    while(prgm_running)
    {
        SDL_Event event; 
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT : 
                    prgm_running = SDL_FALSE; 
                    break; 
                default :
                    break; 
            }
        }
    }
    
    SDL_DestroyTexture(texture_gameBoard); //Détruit les textures restantes
    SDL_DestroyRenderer(renderer); //Detruit le render
    SDL_DestroyWindow(window); //Détruit la fenetre
    SDL_Quit(); //Quitte la sdl

    return EXIT_SUCCESS;
}