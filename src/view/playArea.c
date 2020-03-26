#include "viewUtils.h" 

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; //Pointeur sur la fenêtre
    SDL_Renderer *renderer = NULL; //Pointeur sur le renderer
    SDL_Texture *texture_foreground, *texture_background = NULL; 

    initSDLbasics(&window, &renderer, "Zone de jeu"); //Initialise les bases de la sdl (fenetre, renderer)

    texture_foreground = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                            SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
    if(texture_foreground == NULL)
        SDL_ExitWithError("Erreur création texture");

    texture_background = loadImage(renderer, "../ressources/img/fond_jeu.bmp");  //Charge l'image dans la texture
    
    setGameBoard(&renderer, texture_foreground, texture_background); //Mise en place de la zone de jeu
    SDL_RenderPresent(renderer); //Maj de l'affichage 
 
    SDL_Delay(5000); //Pause 

    SDL_DestroyTexture(texture_foreground); 
    SDL_DestroyTexture(texture_background); 
    SDL_DestroyRenderer(renderer); //Detruit le render
    SDL_DestroyWindow(window); //Détruit la fenetre
    SDL_Quit(); //Quitte la sdl

    return EXIT_SUCCESS;
}