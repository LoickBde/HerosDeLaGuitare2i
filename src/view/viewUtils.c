#include "viewUtils.h" 

//Gére les erreurs
void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

//Init SDL ainsi qu'une fenetre et un renderer
void initSDLbasics(SDL_Window **window, SDL_Renderer **renderer, const char *windowTitle)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) //Init la video de la sdl2
        SDL_ExitWithError("Erreur init SDL2");
    
    //Titre, pos x, pos y, taille x, taille y, options fenetre
    *window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
    if(*window == NULL)
        SDL_ExitWithError("Erreur création fenêtre");

    //Fenetre a associe, pilote (-1 = premier qui correspond), méthode pour afficher le rendu
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED); 
    if(*renderer == NULL)
        SDL_ExitWithError("Erreur création renderer");
    SDL_RenderClear(*renderer);
}

SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path)
{
    SDL_Surface *surface_img = NULL; //Pointeur sur la surface temporaire (pour charger une image)
    SDL_Texture *texture_img = NULL; //Pointeur sur la texture contenat l'image

    surface_img = SDL_LoadBMP(path); //Charge l'image 
    if(surface_img == NULL)
        SDL_ExitWithError("Erreur création surface a partir d'une image");   
    texture_img = SDL_CreateTextureFromSurface(renderer, surface_img); //Crée une texture a partir de l'image = texture contenat l'image
    if(texture_img == NULL)
        SDL_ExitWithError("Erreur création texture à partir d'images"); 
    SDL_FreeSurface(surface_img);

    return texture_img; 
}


//Dessine le tableau de jeu
void drawGameBoard(SDL_Renderer *renderer)
{
    int nbDiv = 5; //NbStrings = nbDiv -1 
    int sizeSide = 150; 
    int sizeBottom = 80; 
    int sizeGuitar = WIDTH - sizeSide*2; 
    int sizeGap = sizeGuitar/nbDiv; 

    if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0) //Couleur blanche
        SDL_ExitWithError("Erreur mise en place de la coueleur blanche");

    //Dessine les contours
    //Render, x1, y1, x2, y2
    if(SDL_RenderDrawLine(renderer, sizeSide, 0, sizeSide, HEIGHT) != 0) //Bord gauche
        SDL_ExitWithError("Erreur dessin ligne bord gauche");
    if(SDL_RenderDrawLine(renderer, WIDTH-sizeSide, 0, WIDTH-sizeSide, HEIGHT) != 0) //Bord droit
        SDL_ExitWithError("Erreur dessin ligne bord droit");
    if(SDL_RenderDrawLine(renderer, sizeSide, HEIGHT-sizeBottom, WIDTH-sizeSide, HEIGHT-sizeBottom) != 0) //Ligne du bas
        SDL_ExitWithError("Erreur dessin ligne ligne du bas");  

    //Dessine les cordes
    int currentX = sizeSide + sizeGap; 
    while(currentX < sizeGuitar+sizeSide)
    {      
        if(SDL_RenderDrawLine(renderer, currentX, 0, currentX, HEIGHT) != 0) //Chaque corde
            SDL_ExitWithError("Erreur dessin cordes guitare");
        currentX+= sizeGap; 
    }
}

void setGameBoard(SDL_Renderer **renderer, SDL_Texture *texture_foreground, SDL_Texture *texture_background)
{    
    SDL_SetRenderTarget(*renderer, texture_foreground); //Texture rendu cible  
    if(SDL_RenderClear(*renderer) != 0) //Clear le foreground
        SDL_ExitWithError("Erreur clear renderer");
    if(SDL_RenderCopy(*renderer, texture_background, NULL, NULL) != 0)
        SDL_ExitWithError("Erreur rendercopy");; 
    drawGameBoard(*renderer);//Dessin sur la texture
    if(SDL_SetRenderTarget(*renderer, NULL) != 0) // La cible de rendu est de nouveau le renderer
        SDL_ExitWithError("Erreur change render target"); 
    if(SDL_RenderCopy(*renderer, texture_foreground, NULL, NULL) != 0)
        SDL_ExitWithError("Erreur rendercopy");;  
}