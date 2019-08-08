#ifndef GESTION_TABLEAU_H
#define GESTION_TABLEAU_H

#include "commun.h"

void afficher_tableau(int*, int);

void remplissage_listes(int* nb_cartes_pioches[NB_PIOCHE][2]);

void shuffle(int*, int);

void lecture_fichier(int* nb_cartes_pioches[NB_PIOCHE][2], char*);

int trouver_pioche(char*);

#endif
