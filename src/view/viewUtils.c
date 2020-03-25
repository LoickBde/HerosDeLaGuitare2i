#include "viewUtils.h" 

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

int initGameBoard(SDL_Renderer *renderer, SDL_Color color)
{
    int nbDiv = 5; //NbStrings = nbDiv -1 
    int sizeSide = 150; 
    int sizeBottom = 80; 
    int sizeGuitar = WIDTH - sizeSide*2; 
    int sizeGap = sizeGuitar/nbDiv; 

    //Couleur de fond 
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0) //Prépare la couleur
        return -1; 
    if(SDL_RenderClear(renderer) != 0) //Change la couleur
        return -1;   

    if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) != 0) //Couleur blanche
        return -1;

    //Dessine les contours
    if(SDL_RenderDrawLine(renderer, sizeSide, 0, sizeSide, HEIGHT) != 0) //Bord gauche
        return -1; 
    if(SDL_RenderDrawLine(renderer, WIDTH-sizeSide, 0, WIDTH-sizeSide, HEIGHT) != 0) //Bord droit
        return -1; 
    if(SDL_RenderDrawLine(renderer, sizeSide, HEIGHT-sizeBottom, WIDTH-sizeSide, HEIGHT-sizeBottom) != 0) //Ligne du bas
        return -1;  

    //Dessine les cordes
    int currentX = sizeSide + sizeGap; 
    printf("%d\n", currentX); 
    while(currentX < sizeGuitar+sizeSide)
    {      
        if(SDL_RenderDrawLine(renderer, currentX, 0, currentX, HEIGHT) != 0) 
            return -1; 
        currentX+= sizeGap; 
        printf("%d\n", currentX); 
    }
    
    SDL_RenderPresent(renderer); //Maj de l'affichage
    return 0; 
}