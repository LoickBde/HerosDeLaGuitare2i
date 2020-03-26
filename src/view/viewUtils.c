#include "viewUtils.h" 

//Gére les erreurs
void SDL_ExitWithError(const char *message, const char *SDL_Error)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_Error);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

//Dessine le tableau de jeu
int initGameBoard(SDL_Renderer *renderer, SDL_Color color)
{
    int nbDiv = 5; //NbStrings = nbDiv -1 
    int sizeSide = 150; 
    int sizeBottom = 80; 
    int sizeGuitar = WIDTH - sizeSide*2; 
    int sizeGap = sizeGuitar/nbDiv; 
     
    if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0) //Couleur blanche
        return -1;

    //Dessine les contours
    //Render, x1, y1, x2, y2
    if(SDL_RenderDrawLine(renderer, sizeSide, 0, sizeSide, HEIGHT) != 0) //Bord gauche
        return -1; 
    if(SDL_RenderDrawLine(renderer, WIDTH-sizeSide, 0, WIDTH-sizeSide, HEIGHT) != 0) //Bord droit
        return -1; 
    if(SDL_RenderDrawLine(renderer, sizeSide, HEIGHT-sizeBottom, WIDTH-sizeSide, HEIGHT-sizeBottom) != 0) //Ligne du bas
        return -1;  

    //Dessine les cordes
    int currentX = sizeSide + sizeGap; 
    while(currentX < sizeGuitar+sizeSide)
    {      
        if(SDL_RenderDrawLine(renderer, currentX, 0, currentX, HEIGHT) != 0) //Chaque corde
            return -1; 
        currentX+= sizeGap; 
    }
    
    return 0; 
}

int setGameBackground(SDL_Renderer *renderer)
{
    return 0; 
}