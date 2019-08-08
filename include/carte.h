#ifndef CARTE_H
#define CARTE_H

#include "chara.h"

typedef enum effet{RIEN_EFFET = 0, SOIN, TP, DEGAT, CHANGE_CHARA/*, ... */} Effet;

typedef enum utilisation{RIEN_UTILISATION = 0, INSTANT, CONTINUE, EQUIPEMENT, UNIQUE} Utilisation;

typedef enum type_carte{COMMUN = 0, RARE_FORCE, RARE_DETER, RARE_CHARISME, EPIQUE_FORCE, EPIQUE_DETER, EPIQUE_CHARISME, CHANCE, MALUS, VILAIN} Type_Carte;


/* Structure de pile */
typedef struct carte Carte;

typedef struct perso Perso;

struct carte {
	/* Informations de la carte */
	char* nom_carte;
	Effet effet; /** < Effet de la carte. */ /* TODO MAJ A FAIRE PAR RAPPORT A LA CONCEPTION */
	Utilisation utilisation; /** < Moment de l'utilisation de l'effet. */
	Chara* chara; /** < Pointeur vers les charactéristiques de la carte (NULL si pas une carte de combat). Si carte de bonus, bien remplir les champs avec le svaleurs à ajouter. */
	char* chemin; /** < Chemin de l'image de la carte */

	Carte* prec; /** < Carte précédente (Carte appartient à une pile, donc la carte directement en dessous (NULL si cette carte est la dernière). */
	Carte* suiv; /** < Carte suivante (Quand elle est dans la main) */

	Perso* perso;

};

struct perso {
	Chara* chara;
	int pv;
	char* anime;
};

void carte_afficher(Carte*);

int carte_init(Carte**, char*, Effet, Utilisation, Chara*, char*, Carte*);

int carte_detruire(Carte**);

int carte_get_nom(Carte*, char**);

int carte_get_prec(Carte*, Carte**);

int carte_null(Carte*);

#endif
