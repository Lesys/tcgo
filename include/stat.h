#ifndef STAT_H
#define STAT_H

#include "fonctions.h"

#define HP_NULL -1
#define ATTAQUE_NULL -1
#define COUT_NULL -1
#define NO_STAT 'X'

typedef struct statistique {
	int hp; /** < Pour tous */
	int attaque; /** < Uniquement pour un PERSONNAGE */
} Stat;

//int stat_null(Stat);

void stat_afficher(Stat);

/* Début accesseurs / mutateurs */
int stat_get_hp(Stat*, int*);
int stat_set_hp(Stat*, int);

int stat_get_attaque(Stat*, int*);
int stat_set_attaque(Stat*, int);


/* Copie le second dans le premier*/
int stat_copie(Stat*, Stat);
int stat_init(Stat*, int, int);

#endif
