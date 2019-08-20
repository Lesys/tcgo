#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/terrain.h"

void terrain_afficher(Terrain* terrain) {
	if (DEBUG)
		fprintf(stderr, "Affichage d'une terrain\n");

	Terrain* prec;

	if (terrain_null(terrain) && DEBUG)
		fprintf(stderr, "terrain null\n");
	else if (!terrain_get_prec(terrain, &prec)) {
		char* ref = NULL;
		int check = terrain_get_ref(terrain, &ref);

		if (!check) {
			if (DEBUG)
				fprintf(stderr, "Terrain actuelle:");

			printf("%s\n", ref);
			free(ref);
			ref = NULL;
		}

		if (!terrain_null(prec)) {
			check = terrain_get_ref(prec, &ref);

			if (!check) {
				if (DEBUG)
					fprintf(stderr, "Terrain précédente: %s\n", ref);
				free(ref);
				ref = NULL;
			}
		}
		else
			if (DEBUG)
				fprintf(stderr, "La terrain précédente est NULL\n");

/*		stat_afficher(terrain->stat);*/
	}
	else
		if (DEBUG)
			fprintf(stderr, "Affichage terrain: Problème lors de la récupération de la terrain précédente\n");

	if (DEBUG)
		fprintf(stderr, "Fin affichage d'une terrain\n");
}

/*struct terrain {
        char* nom_terrain;
        Effet effet;
        Utilisation utilisation; 
        Stat* stat;
};
*/

int terrain_null(Terrain* t) {
	return (t == NULL);
}

int terrain_get_heros(Terrain* t, Carte** heros) {
	int retour = 0;

	if (!terrain_null(t))
		*heros = t->heros;
	else
		retour = 1;

	return retour;
}

int terrain_set_heros(Terrain* t, Carte* heros) {
	int retour = 0;

	if (!terrain_null(t))
		t->heros = heros;
	else
		retour = 1;

	return retour;
}

int terrain_recuperer_perso(Terrain* t, Carte** c) {
	int retour = 0;

	if (!terrain_null(t)) {
		int choix = -1, choix2 = -1;

		do {
			if (choix != -1)
				printf("Votre choix ne correspond pas à un choix possible, refaire la saisie.\n");

			printf("Veuillez choisir une zone pour y récupérer un personnage: \n1°) Défense\n2°) Attaque\n0°) Annuler\nVotre choix: ");
			scanf("%d", &choix);
		} while ((choix < 1 && choix > NB_ZONE) && choix != 0);

		if (choix) {
			int retour1 = 0, retour2 = 0, retour3 = 0;
			char* ref1 = NULL, *ref2 = NUL, *ref3 = NULL;
			retour1 = carte_get_ref(t->zone[0][choix - 1], &ref1);
			retour2 = carte_get_ref(t->zone[1][choix - 1], &ref2);
			retour3 = carte_get_ref(t->zone[2][choix - 1], &ref3);

			do {
				if (choix2 != -1)
					printf("Votre choix ne correspond pas à un choix possible, refaire la saisie.\n");

				printf("Veuillez choisir la carte à récupérer: \n1°) %s \t2°) %s\t3°) %s\n0°) Annuler\nVotre choix: ", retour1 == 0? ref1 : "VIDE", retour2 == 0? ref2 : "VIDE", retour3 == 0? ref3 : "VIDE");
				scanf("%d", &choix2);
			} while ((choix2 < 1 || choix2 > NB_EMPLACEMENT_ZONE) && choix2 != 0);

			if (choix2)
				*c = t->zone[choix2 - 1][choix - 1];
			else
				retour = 3; /* L'utilisateur a annulé le 2ème choix */
		}
		else
			retour = 2; /* L'utilisateur a annulé le 1er choix */
	}
	else
		retour = 1; /* Terrain NULL */

	return retour;
}

int terrain_poser_perso(Terrain* t, Carte* c) {
	int retour = 0;

	if (!terrain_null(t)) {
		int choix = -1, choix2 = -1;

		do {
			if (choix != -1)
				printf("Votre choix ne correspond pas à un choix possible, refaire la saisie.\n");

			printf("Veuillez choisir une zone pour y poser le personnage: \n1°) Défense\n2°) Attaque\n0°) Annuler\nVotre choix: ");
			scanf("%d", &choix);
		} while ((choix < 1 && choix > NB_ZONE) && choix != 0);

		if (choix) {
			int retour1 = 0, retour2 = 0, retour3 = 0;
			char* ref1 = NULL, *ref2 = NUL, *ref3 = NULL;
			retour1 = carte_get_ref(t->zone[0][choix - 1], &ref1);
			retour2 = carte_get_ref(t->zone[1][choix - 1], &ref2);
			retour3 = carte_get_ref(t->zone[2][choix - 1], &ref3);

			do {
				if (choix2 != -1)
					printf("L'emplacement sélectionné est déjà occupé par un personnage, refaire la saisie\n");

				choix = -1;
				do {
					if (choix2 != -1)
						printf("Votre choix ne correspond pas à un choix possible, refaire la saisie.\n");

					printf("Veuillez choisir un emplacement vide pour y poser le personnage: \n1°) %s \t2°) %s\t3°) %s\n0°) Annuler\nVotre choix: ", retour1 == 0? ref1 : "VIDE", retour2 == 0? ref2 : "VIDE", retour3 == 0? ref3 : "VIDE");
					scanf("%d", &choix2);
				} while ((choix2 < 1 || choix2 > NB_EMPLACEMENT_ZONE) && choix2 != 0); /* Tant que la saisie n'est pas bonne */
			} while (choix2 != 0 && !carte_null(t->zone[choix2 - 1][choix - 1])); /* Tant que la saisie est faite sur un emplacement déjà pris */

			if (choix2)
				t->zone[choix2 - 1][choix - 1] = c;
			else
				retour = 3; /* L'utilisateur a annulé le 2ème choix */
		}
		else
			retour = 2; /* L'utilisateur a annulé le 1er choix */
	}
	else
		retour = 1; /* Terrain NULL */

	return retour;
}

int terrain_detruire(Terrain** t) {
	int retour = 0;

	if (!terrain_null(*t)) {
		if ((*t)->ref != NULL)
			free((*t)->ref);

		if ((*t)->nom_terrain != NULL)
			free((*t)->nom_terrain);

		if ((*t)->nom_anime != NULL)
			free((*t)->nom_anime);

		if ((*t)->chemin != NULL)
			free((*t)->chemin);

/*		if ((*t)->stat != NULL)
			stat_detruire(&((*t)->stat));
*/
		free(*t);
		*t = NULL;
	}
	else
		retour = 1;

	return retour;
}

int terrain_init(Terrain** t, char* ref, char* nom_terrain, char* nom_anime, int heros/*, Effet effet*/, Utilisation utilisation, Stat* stat, char* themin, Terrain* prec) {
	int retour = 0;

	if (!terrain_null(*t))
		terrain_detruire(t);

	if (((*t) = malloc(sizeof(Terrain))) != NULL) {
		(*t)->ref = NULL;
		(*t)->nom_anime = NULL;
		(*t)->nom_terrain = NULL;
		(*t)->chemin = NULL;
		(*t)->stat = NULL;
		(*t)->prec = NULL;
		(*t)->suiv = NULL;

		retour = terrain_set_ref(*t, ref);

		if (!retour) {
			retour = terrain_set_nom(*t, nom_terrain);

			if (!retour) {
				retour = terrain_set_nom_anime(*t, nom_anime);

				if (!retour) {
					retour = terrain_set_heros(*t, heros);

					if (!retour) {
						retour = terrain_set_utilisation(*t, utilisation);

						if (!retour) {
							retour = terrain_set_stat(*t, stat);

							if (!retour) {
								retour = terrain_set_chemin(*t, chemin);

								if (!retour) {
									retour = terrain_set_prec(*t, prec);

									if (retour)
										retour = 9; /* Problème set prec */
								}
								else
									retour = 8; /* Problème set chemin */
							}
							else
								retour = 7; /* Problème set stat */
						}
						else
							retour = 6; /* Problème set utilisation */
					}
					else
						retour = 5; /* Problème set heros */
				}
				else
					retour = 4; /* Problème set nom anime */
			}
			else
				retour = 3; /* Problème set nom */
		}
		else
			retour = 2; /* Problème set ref */

		if (retour)
			terrain_detruire(t);
	}
	else
		retour = 1; /* Problème malloc */

	return retour;
}
