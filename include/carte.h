#ifndef CARTE_H
#define CARTE_H

#include <string.h>
#include "stat.h"
/*#include "effet.h"*/

#define HEROS "Héros"
#define PERSONNAGE "Perso"
#define SORT "Sort"

typedef enum type_carte{TYPE_HEROS = 0, TYPE_PERSONNAGE, TYPE_SORT} Type_Carte;

/* Macro retournant le type de la carte (SORT par défaut) */
#define Type_Carte_fnc(type) (strcmp(type, HEROS) == 0? TYPE_HEROS : (strcmp(type, PERSONNAGE) == 0? TYPE_PERSONNAGE : TYPE_SORT))
#define Type_Carte_fnc_inv(type) (type == TYPE_HEROS? HEROS : (type == TYPE_PERSONNAGE? PERSONNAGE : SORT))

/* Structure de pile */
typedef struct carte Carte;

/*typedef struct perso Perso;*/


typedef enum type_effet{RIEN_EFFET = 0, SOIN, DEGAT, BOOST, DETRUIRE/*, ... */} Type_Effet;

typedef enum cible{ALLY_TO_ENNEMY = 0, ALLY_TO_ALLY} Cible;

typedef union temp {
	Stat stat;
	int boost;
	Carte* equip;
} Temp;

typedef struct effet {
	Type_Effet type_effet;
	Temp* tmp;
} Effet;

typedef enum utilisation{RIEN_UTILISATION = 0, INSTANT, TERRAIN, EQUIPEMENT, UNIQUE} Utilisation;


struct carte {
	/* Informations de la carte */
	char* ref; /** < Référence de la carte (ex: PD-001) */
	Type_Carte type; /** < Type de carte (enum) */
	char* nom_carte; /* < Le nom de la carte */
	char* nom_anime; /** < Le nom de l'animé correspondant */
	int cout; /** < Coût en énergie (-1 si HEROS, ne peut pas être < à 0 si SORT ou PERSONNAGE) */
	Effet effet; /** < Effet de la carte. */ /* TODO MAJ A FAIRE PAR RAPPORT A LA CONCEPTION */
	Utilisation utilisation; /** < Moment de l'utilisation de l'effet. */
	Stat stat; /** < Stoque les HP de la carte (-1 si pas de HP) ainsi que son attaque (-1 si pas d'attaque)*/
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

int carte_null(Carte*);

/* Début accesseurs / mutateurs */
int carte_get_ref(Carte*, char**);
int carte_set_ref(Carte*, char*);

int carte_get_type(Carte*, Type_Carte*);
int carte_set_type(Carte*, Type_Carte);

int carte_get_nom(Carte*, char**);
int carte_set_nom(Carte*, char*);

int carte_get_nom_anime(Carte*, char**);
int carte_set_nom_anime(Carte*, char*);

int carte_get_cout(Carte*, int*);
int carte_set_cout(Carte*, int);

int carte_get_prec(Carte*, Carte**);
int carte_set_prec(Carte*, Carte*);

int carte_get_effet(Carte*, Effet*);
int carte_set_effet(Carte*, Effet);

int carte_get_utilisation(Carte*, Utilisation*);
int carte_set_utilisation(Carte*, Utilisation);

int carte_get_stat(Carte*, Stat*);
int carte_set_stat(Carte*, Stat);

int carte_get_chemin(Carte*, char**);
int carte_set_chemin(Carte*, char*);
/* Fin accesseurs / mutateurs */

int carte_copier(Carte*, Carte**);
int carte_detruire(Carte**);
int carte_init(Carte**, char*, Type_Carte, char*, char*, int /*, Effet */, Utilisation, Stat, char*, Carte*);


#endif
