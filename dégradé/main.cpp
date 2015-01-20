#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

void pause();

int main(int argc, char *argv[])
{   
    /* Initialisation d'une surface sur *ecran et *lignes qui contient 256 place dans son tableau .  */
    SDL_Surface *ecran = NULL, *lignes[256] = {NULL};
    SDL_Rect position;  // Initialisation d'une varaiable *position.
    int i = 0;

    SDL_Init(SDL_INIT_VIDEO);   // Initialisation de la vidéo. 

    ecran = SDL_SetVideoMode(640, 256, 32, SDL_HWSURFACE); // Configuration du mode vidéo.
    
    /* Génération d'une boucle créant chaque *ligne du tableau. */
    for (i = 0 ; i <= 255 ; i++) 
        lignes[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 640, 1, 32, 0, 0, 0, 0);

    SDL_WM_SetCaption("Mon dégradé en SDL !", NULL); // Affichage d'un titre.

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // Gestion de la couleur sur *ecran 

    /* Génération d'une boucle de positionnement */
    for (i = 0 ; i <= 255 ; i++)
    {
        position.x = 0; // Les lignes sont à gauche (abscisse de 0)
        position.y = i; // La position verticale dépend du numéro de la ligne
        SDL_FillRect(lignes[i], NULL, SDL_MapRGB(ecran->format, i, i, i));
        SDL_BlitSurface(lignes[i], NULL, ecran, &position);
    }

    SDL_Flip(ecran);
    pause();

    for (i = 0 ; i <= 255 ; i++) // N'oubliez pas de libérer les 256 surfaces
        SDL_FreeSurface(lignes[i]);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void pause() // Verrouillage de ma fenêtre
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
