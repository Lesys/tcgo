#ifndef PIOCHE_H
#define PIOCHE_H

#include "carte.h"

typedef struct pioche Pioche;

struct pioche {
	Carte* sommet; /** < Liste des cartes de la pioche (pile) */
/*	int nb_carte;*/ /** < Le nombre  */
};

int pioche_get_sommet(Pioche*, Carte**);
int pioche_set_sommet(Pioche*, Carte*);

void pioche_afficher(Pioche*);

int pioche_vide(Pioche*);
int pioche_null(Pioche*);

int pioche_limite_exemplaire(Pioche*, Carte*);

int pioche_depiler(Pioche*, Carte**);
int pioche_empiler(Pioche*, Carte*);
int pioche_recup_carte_par_emplacement(Pioche*, int, Carte**);
int pioche_echanger_carte(Pioche*, Pioche*);
int pioche_melanger(Pioche*);

int pioche_nb_carte(Pioche*, int*);
int pioche_remettre(Pioche*, Carte*);
int pioche_enlever_par_ref(Pioche*, char*, Carte**); /* Pour enlever une carte, il faut "sauvegarder" la carte précédente de la pile pour pouvoir changer son "prec" */

int pioche_init(Pioche**, char*);
int pioche_detruire(Pioche**);



#endif
