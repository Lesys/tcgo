#ifndef JOUEUR_H
#define JOUEUR_H

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
	Carte* heros; /** < Toutes les cartes héros du joueur (représente la première carte de la liste) */
	Carte* bonus; /** < Toutes les cartes bonus du joueur (représente la première carte de la liste) */
	Carte* structure; /** < Toutes les structures du joueur (représente la première carte de la liste) */

	int nb_chance_max; /** < Le nombre de carte chance maximum que le joueur peut posséder (peut diminuer ou augmenter; commence à 3) */
	int nb_struct_max; /** < Le nombre de carte de structure que le joueur peut posséder (+1 par personnage donnant une structure; commence à 0) */

	char* pseudo; /** < Pseudonyme du joueur */
	Couleur couleur; /** < Couleur du joueur (Nécessaire?) */
	int score; /** < Score du joueur (s'actualisé à chaque mort d'un vilain) */

	Type_Joueur type; /** < Type du joueur (Local, distant ou bot) */
	Joueur* suiv; /** < Joueur suivant le joueur actuel */
	int sockfd; /** < Numéro de socket (uniquement pour les joueurs distants; 0 de base) */
};

/* Accesseurs et mutateurs */
int joueur_get_heros(Joueur*, Carte**, int); /* Numéro de la carte désirée */
int joueur_ajouter_heros(Joueur*, Carte*);
int joueur_get_nb_heros(Joueur*, int*);

int joueur_get_chance(Joueur*, Carte**, int);
int joueur_ajouter_chance(Joueur*, Carte*);
int joueur_get_nb_chance_max(Joueur*, int*);

int joueur_get_structure(Joueur*, Carte**, int);
int joueur_ajouter_structure(Joueur*, Carte*);
int joueur_get_nb_structure_max(Joueur*, int*);

int joueur_get_pseudo(Joueur*, char**);
int joueur_set_pseudo(Joueur*, char*);

int joueur_get_couleur(Joueur*, Couleur*);
int joueur_set_couleur(Joueur*, Couleur);

int joueur_get_score(Joueur*, int*);
int joueur_set_score(Joueur*, int);

int joueur_get_type(Joueur*, Type_Joueur*);
int joueur_set_type(Joueur*, Type_Joueur);

int joueur_get_suiv(Joueur*, Joueur**);
int joueur_set_suiv(Joueur*, Joueur*);

int joueur_get_sockfd(Joueur*, int*);
int joueur_set_sockfd(Joueur*, int);

#endif
