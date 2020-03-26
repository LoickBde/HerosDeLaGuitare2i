#include "viewUtils.h" 

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; //Pointeur sur la fenêtre
    SDL_Renderer *renderer = NULL; //Pointeur sur le renderer
    SDL_Surface *surface_img = NULL; //Pointeur sur la surface temporaire (pour charger une image)
    SDL_Texture *texture_foreground, *texture_background = NULL; 
    SDL_Color Color_BlueGrey = {79,109,122,SDL_ALPHA_OPAQUE}; //r, g, b, opacité

    if(SDL_Init(SDL_INIT_VIDEO) != 0) //Init la video de la sdl2
        SDL_ExitWithError("Erreur init SDL2", SDL_GetError());
    
    //Titre, pos x, pos y, taille x, taille y, options fenetre
    window = SDL_CreateWindow("Zone de jeu !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
    if(window == NULL)
        SDL_ExitWithError("Erreur création fenêtre", SDL_GetError());

    //Fenetre a associe, pilote (-1 = premier qui correspond), méthode pour afficher le rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
    if(renderer == NULL)
        SDL_ExitWithError("Erreur création renderer", SDL_GetError());
    SDL_RenderClear(renderer);

    texture_foreground = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                            SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
    if(texture_foreground == NULL)
        SDL_ExitWithError("Erreur création texture", SDL_GetError());

    surface_img = SDL_LoadBMP("../ressources/img/fond_jeu.bmp"); //Charge l'image 
    if(surface_img == NULL)
        SDL_ExitWithError("Erreur création surface a partir d'une image", SDL_GetError());   

    texture_background = SDL_CreateTextureFromSurface(renderer, surface_img); 
    if(texture_background == NULL)
        SDL_ExitWithError("Erreur création texture à partir d'images", SDL_GetError()); 
    SDL_FreeSurface(surface_img);
        
     
    SDL_SetRenderTarget(renderer, texture_foreground); //Texture rendu cible  
    if(SDL_RenderClear(renderer) != 0) //Clear le foreground
        return -1;  
    SDL_RenderCopy(renderer, texture_background, NULL, NULL); 
    if(initGameBoard(renderer, Color_BlueGrey) != 0) //Dessin sur la texture
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