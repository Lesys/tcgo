#ifndef CARTE_H
#define CARTE_H

#include "stat.h"
/*#include "effet.h"*/

/* Structure de pile */
typedef struct carte Carte;

/*typedef struct perso Perso;*/


typedef enum type_effet{RIEN_EFFET = 0, SOIN, DEGAT, BOOST, DETRUIRE/*, ... */} Type_Effet;

typedef enum cible{ALLY_TO_ENNEMY = 0, ALLY_TO_ALLY} Cible;

typedef union temp {
	Stat* stat;
	int boost;
	Carte* equip;
} Temp;

typedef struct effet {
	Type_Effet type_effet;
	Temp* tmp;
} Effet;

typedef enum utilisation{RIEN_UTILISATION = 0, INSTANT, TERRAIN, EQUIPEMENT, UNIQUE} Utilisation;

/*typedef enum type_carte{HEROS = 0, PERSONNAGE, SORT} Type_Carte;*/


struct carte {
	/* Informations de la carte */
	char* ref; /** < Référence de la carte (ex: PD-001) */
	char* nom_carte; /* < Le nom de la carte */
	char* nom_anime; /** < Le nom de l'animé correspondant */
	int cout; /** < Coût en énergie (-1 si HEROS, ne peut pas être < à 0 si SORT ou PERSONNAGE) */
	Effet effet; /** < Effet de la carte. */ /* TODO MAJ A FAIRE PAR RAPPORT A LA CONCEPTION */
	Utilisation utilisation; /** < Moment de l'utilisation de l'effet. */
	Stat* stat; /** < UNION: soit HP (HEROS) soit statistiques de la carte (PERSONNAGE) (NULL si un sort).*/
	char* chemin; /** < Chemin de l'image de la carte */

	Carte* prec; /** < Carte précédente (Carte appartient à une pile, donc la carte directement en dessous (NULL si cette carte est la dernière). */
	Carte* suiv; /** < Carte suivante (Quand elle est dans la main) */

/*	Perso* perso;*/

};
/*
struct perso {
	Chara* chara;
	int pv;
	char* anime;
};*/

void carte_afficher(Carte*);

int carte_init(Carte**, char*, char*, char*, int/*, Effet*/, Utilisation, Stat*, char*, Carte*);

int carte_detruire(Carte**);

int carte_get_ref(Carte*, char**);
int carte_get_nom(Carte*, char**);
int carte_get_anime(Carte*, char**);
int carte_get_cout(Carte*, int*);

int carte_get_prec(Carte*, Carte**);

int carte_null(Carte*);

#endif