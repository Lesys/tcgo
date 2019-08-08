#ifndef PIOCHE_H
#define PIOCHE_H

#include "carte.h"

typedef struct pioche Pioche;

typedef struct liste_pioche {
	Pioche* p;
	Pioche* first;
} Liste_Pioche;

struct pioche {
//      char* nom_pioche;
	Type_Carte type; /** < Type de la pioche */
	Carte* sommet; /** < Liste des cartes de la pioche (pile) */
};

int pioche_get_sommet(Pioche*, Carte**);
int pioche_set_sommet(Pioche*, Carte*);
int pioche_get_type(Pioche*, Type_Carte*);
int pioche_set_type(Pioche*, Type_Carte);

void pioche_afficher(Pioche*);

int pioche_vide(Pioche*);
int pioche_null(Pioche*);

int pioche_depiler(Pioche*, Carte**);
int pioche_empiler(Pioche*, Carte*);

int pioche_init(Pioche**, Type_Carte);
int pioche_detruire(Pioche**);



#endif
