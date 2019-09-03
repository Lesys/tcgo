#ifndef JOUEUR_H
#define JOUEUR_H

#include "pioche.h"
#include "terrain.h"

#define NB_JOUEUR_MIN 1
#define NB_JOUEUR_MAX 2
#define TAILLE_PSEUDO 15

typedef struct pioche Pioche;

/**
	\typedef Type_Joueur : Type du joueur (BOT, LOCAL ou DISTANT)
*/
typedef enum type_joueur {BOT = 0, LOCAL, DISTANT} Type_Joueur;

/**
	\typedef Joueur : Un joueur
*/
typedef struct joueur Joueur;

/* Structure d'un Joueur */
/**
	\struct joueur
	\brief Structure d'un Joueur
*/
struct joueur {
	Pioche* deck; /** < Tout le paquet de carte du joueur. */
	Pioche* hand; /** < La main du joueur pendant le jeu. */
	Pioche* defausse;

	Terrain* terrain; /** < Terrain du joueur. Regroupe son héros, ses cartes personnages en zone d'attaque et défense ainsi que ses cartes sorts. */
	char* pseudo; /** < Pseudonyme du joueur */

	Type_Joueur type; /** < Type du joueur (Local, distant ou bot) */
	Joueur* suiv; /** < Joueur suivant le joueur actuel */
	Joueur* prec; /** < Joueur précédent le joueur actuel (uniquement pour la destruction) */
	int sockfd; /** < Numéro de socket (uniquement pour les joueurs distants; 0 de base) */

	int abandon;
};


int joueur_null(Joueur*);

/* Accesseurs et mutateurs */

int joueur_get_deck(Joueur*, Pioche**);
int joueur_set_deck(Joueur*, Pioche*);

int joueur_get_main(Joueur*, Pioche**);
int joueur_set_main(Joueur*, Pioche*);

int joueur_get_defausse(Joueur*, Pioche**);
int joueur_set_defausse(Joueur*, Pioche*);

int joueur_get_terrain(Joueur*, Terrain**);
int joueur_set_terrain(Joueur*, Terrain*);

int joueur_get_pseudo(Joueur*, char**);
int joueur_set_pseudo(Joueur*, char*);

int joueur_get_type(Joueur*, Type_Joueur*);
int joueur_set_type(Joueur*, Type_Joueur);

int joueur_get_suivant(Joueur*, Joueur**);
int joueur_set_suivant(Joueur*, Joueur*);

int joueur_get_sockfd(Joueur*, int*);
int joueur_set_sockfd(Joueur*, int);

/* Permet d'envoyer une carte d'une pioche à une autre */
int joueur_deck_vers_main(Joueur*);
int joueur_deck_vers_defausse(Joueur*);
int joueur_main_vers_deck(Joueur*);
int joueur_main_vers_defausse(Joueur*);
int joueur_defausse_vers_deck(Joueur*);
int joueur_defausse_vers_main(Joueur*);

int joueur_init(Joueur**);
/*int joueur_detruire(Joueur**);*/
int joueur_liste_detruire(Joueur**);
int joueur_liste_creation(int, Joueur**);

#endif
