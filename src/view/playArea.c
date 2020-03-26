#include "viewUtils.h" 

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; //Pointeur sur la fenêtre
    SDL_Renderer *renderer = NULL; //Pointeur sur le renderer
    SDL_Texture *texture_foreground, *texture_background = NULL; 
    SDL_Color Color_BlueGrey = {79,109,122,SDL_ALPHA_OPAQUE}; //r, g, b, opacité

    initSDLbasics(&window, &renderer, "Zone de jeu"); //Initialise les bases de la sdl (fenetre, renderer)

    texture_foreground = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                            SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
    if(texture_foreground == NULL)
        SDL_ExitWithError("Erreur création texture", SDL_GetError());

    texture_background = loadImage(renderer, "../ressources/img/fond_jeu.bmp");  //Charge l'image dans la texture
     
    SDL_SetRenderTarget(renderer, texture_foreground); //Texture rendu cible  
    if(SDL_RenderClear(renderer) != 0) //Clear le foreground
        return -1;  
    SDL_RenderCopy(renderer, texture_background, NULL, NULL); 
    if(drawGameBoard(renderer, Color_BlueGrey) != 0) //Dessin sur la texture
        SDL_ExitWithError("Erreur init plateau de jeu", SDL_GetError()); 
    SDL_SetRenderTarget(renderer, NULL); // La cible de rendu est de nouveau le renderer. 
    SDL_RenderCopy(renderer, texture_foreground, NULL, NULL); 
     
    SDL_RenderPresent(renderer); //Maj de l'affichage 

    SDL_Delay(5000); //Pause 

    SDL_DestroyTexture(texture_foreground); 
    SDL_DestroyTexture(texture_background); 
    SDL_DestroyRenderer(renderer); //Detruit le render
    SDL_DestroyWindow(window); //Détruit la fenetre
    SDL_Quit(); //Quitte la sdl

    return 0;
}