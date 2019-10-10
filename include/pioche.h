#ifndef PIOCHE_H
#define PIOCHE_H

#define EXTENSION_CARTE ".png"

#include "fonctions.h"
#include "carte.h"
/*#include "stat.h"*/
#include "joueur.h"

#define NB_CARTE_DEPART 5

typedef struct joueur Joueur;

typedef struct pioche Pioche;

struct pioche {
	Carte* sommet; /** < Liste des cartes de la pioche (pile) */
/*	Carte* héros;*/ /** < Le héros du joueur (uniquement pour le deck) */
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

int pioche_piocher_main_depart(Joueur*); /* Permet d'initialiser la main du joueur avec le nombre de carte à piocher au début du jeu */
int pioche_choisir_heros(Joueur*);
int pioche_ref_presente(Pioche*, char*);
int pioche_sauvegarder(Pioche*);
int pioche_charger(Pioche**);
int pioche_recup_par_ref(Pioche*, char*, Carte**);
int creer_deck(Pioche**);

int pioche_detruire(Pioche**);
int pioche_init(Pioche**, int, char*);
int pioche_init_vide(Pioche**);


#endif
