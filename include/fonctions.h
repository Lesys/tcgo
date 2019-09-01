#ifndef FONCTION_H
#define FONCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define NB_EXEMPLAIRE_MAX 3 /* Le nombre d'exemplaire maximum d'une même carte dans un deck */
#define NB_EXEMPLAIRE_SEMI_LIMITE 2 /* Nombre d'exemplaires autorisés pour les semi-limitées */
#define NB_EXEMPLAIRE_LIMITE 1 /* Nobmre d'exemplaires autorisés pour les limitées */

#define LISTE_CARTES_EMPLACEMENT "../include/cartes.txt"

#define NB_DECK_MAX 40 /* Nombre de cartes maximum pour former un deck */
#define TAILLE_REF 5
#define TAILLE_NOM_FICHIER 15
#define DELIMITEUR_CHAINE ';'


#define DEBUG 0 /* Permet d'afficher les messages de débug (si != 0) */

// Déclarations des fonctions au préalable
/*void afficher_tableau(int*, int);

void choix_nombre_carte(int*, char*);

int prendre_carte(int*, int, int);

int tirer_carte(int* nb_cartes_pioches[NB_PIOCHE][2], int);

void remplissage_listes(int* nb_cartes_pioches[NB_PIOCHE][2]);

void shuffle(int*, int);

void lecture_fichier(int* nb_cartes_pioches[NB_PIOCHE][2], char*);

int trouver_pioche(char*);

int piocher_sans_defausse(int* nb_cartes_pioches[NB_PIOCHE][2], char*);
*/

#endif
