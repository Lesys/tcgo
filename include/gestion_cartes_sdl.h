#ifndef GESTION_CARTES_SDL_H
#define GESTION_CARTES_SDL_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <sys/types.h>
#include <dirent.h>


#define LENGTH_NAME_CARD 20 // Longueur max du nom de la carte

#define PLATEAU_FILE_NAME "plateau.txt"

typedef enum type_case {hopital = 0, heros, chance, malus, vilain} Type_Case;

typedef struct case_plateau {
        case_plateau* droite, *bas, *gauche, *haut;
        Type_Case type;
        int pos_x, pos_y; // Position sur le plateau
} Case;

typedef struct plateau {
        SDL_Surface* p;
        Case tete; // Case inexistante mais servant de référence
        Case* tableau_case;
        int nb_cases;
        int nb_joueurs;
} Plateau;

#endif
