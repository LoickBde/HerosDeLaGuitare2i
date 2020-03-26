#include "viewUtils.h" 

//Gére les erreurs
void SDL_ExitWithError(const char *message, const char *SDL_Error)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_Error);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

//Init SDL ainsi qu'une fenetre et un renderer
int initSDLbasics(SDL_Window **window, SDL_Renderer **renderer, const char *windowTitle)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) //Init la video de la sdl2
        SDL_ExitWithError("Erreur init SDL2", SDL_GetError());
    
    //Titre, pos x, pos y, taille x, taille y, options fenetre
    *window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
    if(*window == NULL)
        SDL_ExitWithError("Erreur création fenêtre", SDL_GetError());

    //Fenetre a associe, pilote (-1 = premier qui correspond), méthode pour afficher le rendu
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED); 
    if(*renderer == NULL)
        SDL_ExitWithError("Erreur création renderer", SDL_GetError());
    SDL_RenderClear(*renderer);
}

SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path)
{
    SDL_Surface *surface_img = NULL; //Pointeur sur la surface temporaire (pour charger une image)
    SDL_Texture *texture_img = NULL; //Pointeur sur la texture contenat l'image

    surface_img = SDL_LoadBMP(path); //Charge l'image 
    if(surface_img == NULL)
        SDL_ExitWithError("Erreur création surface a partir d'une image", SDL_GetError());   
    texture_img = SDL_CreateTextureFromSurface(renderer, surface_img); //Crée une texture a partir de l'image = texture contenat l'image
    if(texture_img == NULL)
        SDL_ExitWithError("Erreur création texture à partir d'images", SDL_GetError()); 
    SDL_FreeSurface(surface_img);

    return texture_img; 
}


//Dessine le tableau de jeu
int drawGameBoard(SDL_Renderer *renderer, SDL_Color color)
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

int setGameBoardBackground(SDL_Renderer *renderer)
{
    return 0; 
}