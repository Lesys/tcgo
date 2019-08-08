#ifndef VARIABLES_H
#define VARIABLES_H

#include "commun.h"

// Variables globales
int NB_HEROS_COMMUNS = 0; // Nombre total de cartes communes

int NB_HEROS_RARES_FORCE = 0; // Nombre total de cartes rares de type force
int NB_HEROS_RARES_DETER = 0; // Nombre total de cartes rares de type détermination
int NB_HEROS_RARES_CHARI = 0; // Nombre total de cartes rares de type charisme

int NB_HEROS_EPIQUES_FORCE = 0; // Nombre total de cartes épiques de type force
int NB_HEROS_EPIQUES_DETER = 0; // Nombre total de cartes épiques de type détermination
int NB_HEROS_EPIQUES_CHARI = 0; // Nombre total de cartes épiques de type charisme

int NB_CHANCES = 0; // Nombre total de cartes chances
int NB_PIEGES = 0; // Nombre total de cartes pièges
int NB_VILAINS = 0; // Nombre total de vilains dans le jeu

char* FILENAME = "../include/liste.txt"; // Nom du fichier à lire avec les quantités de cartes dans chaque pioche

// Nom des pioches avec leur numéro
const char* Pioches[NB_PIOCHE][2] = {{"heros communs", "1"}, {"heros rares force", "2"}, {"heros rares determination", "3"}, {"heros rares charisme", "4"},
	{"heros epiques force", "5"}, {"heros epiques determination", "6"}, {"heros epiques charisme", "7"}, {"chances", "8"}, {"pieges", "9"},
	{"vilains", "10"}};


#endif
