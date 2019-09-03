#ifndef STAT_H
#define STAT_H

#include "fonctions.h"

typedef struct combat {
	int attaque; /* Attaque du PERSONNAGE */
	int hp; /** < Points de vie du PERSONNAGE */
} Combat;

typedef union statistique {
	int hp; /** < Uniquement pour un HEROS */
	Combat* combat;
} Stat;

#endif
