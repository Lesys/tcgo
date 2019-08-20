#ifndef TERRAIN_H
#define TERRAIN_H

#define NB_EMPLACEMENT_ZONE 3 /* Le nombre de cartes posables dans une zone d'attaque ou de défense */
#define NB_ZONE 2 /* Le nombre de zone par joueur sur le terrain (pour l'instant, uniquement 2: zone d'attaque et zone de défense) */
#define NB_SORT 2 /* Le nombre possible de sorts posés simultanéments sur le terrain */

#include "carte.h"

typedef struct terrain Terrain;

struct terrain {
	Carte* heros; /** < Le héros que le joueur incarne pour la partie. Il représente ses points de vie. */
	Carte*[NB_EMPLACEMENT_ZONE][NB_ZONE] zone; /** < Les zones d'attaque et de défense. [X][0] zone de défense, [X][1] zone d'attaque. */
	Carte*[NB_SORT] sort; /** < Les sorts posés sur le terrain. */
};

void terrain_afficher(Terrain*);

int terrain_get_heros(Terrain*, Carte**);
int terrain_set_heros(Terrain*, Carte*);

int terrain_recuperer_perso(Terrain*, Carte**);
int terrain_poser_perso(Terrain*, Carte*);

int terrain_recuperer_sort(Terrain*, Carte**);
int terrain_poser_sort(Terrain*, Carte*);

int terrain_detruire(Terrain**);
int terrain_init(Terrain**);

#endif
