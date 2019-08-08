#ifndef GESTION_CARTES_H
#define GESTION_CARTES_H

#include "commun.h"

void choix_nombre_carte(int*, char*);

int prendre_carte(int*, int, int);

int tirer_carte(int* nb_cartes_pioches[NB_PIOCHE][2], int);

int piocher_sans_defausse(int* nb_cartes_pioches[NB_PIOCHE][2], char*);

#endif
