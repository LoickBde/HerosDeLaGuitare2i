#include "viewUtils.h" 

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; //Pointeur sur la fenêtre
    SDL_Renderer *renderer = NULL; //Pointeur sur le renderer
    SDL_Surface *tmp_srfc = NULL; //Pointeur sur la surface temporaire (pour charger une image)
    SDL_Texture *texture = NULL; 
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

    tmp_srfc = SDL_LoadBMP("../ressources/img/fond_jeu.bmp"); //Charge l'image 
    if(tmp_srfc == NULL)
        SDL_ExitWithError("Erreur création surface a partir d'une image", SDL_GetError());
    texture = SDL_CreateTextureFromSurface(renderer, tmp_srfc); //Render a associer a la texture, la surface a partir de laquelle creer la texture
    SDL_FreeSurface(tmp_srfc); //On libère tout de suite la surface
    if(texture == NULL)
        SDL_ExitWithError("Erreur création texture a partir d'une surface   ", SDL_GetError());

    if(SDL_RenderCopy(renderer, texture, NULL, NULL) != 0) //Renderer dest, texture source, endroit a copier, endroit a mettre la copie 
        SDL_ExitWithError("Erreur copie texttur sur renderer", SDL_GetError());;    

    /* if(initGameBoard(renderer, Color_BlueGrey) != 0)
        SDL_ExitWithError("Erreur init plateau de jeu"); */
    
    SDL_RenderPresent(renderer); //Maj de l'affichage

    SDL_Delay(5000); //Pause 

    SDL_DestroyRenderer(renderer); //Detruit le render
    SDL_DestroyWindow(window); //Détruit la fenetre
    SDL_Quit(); //Quitte la sdl

    return 0;
}