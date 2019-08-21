#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/terrain.h"

void terrain_afficher(Terrain* t) {
	if (DEBUG)
		fprintf(stderr, "Affichage d'une terrain\n");

	if (terrain_null(t) && DEBUG)
		fprintf(stderr, "terrain null\n");
	else {
		int check = 0, i = 0, j = 0;
		char* ref = NULL;

		if (DEBUG)
			fprintf(stderr, "Terrain actuel:\n");

		if (!carte_null(t->heros)) {
			check = carte_get_ref(t->heros, &ref);

			if (!check) {
				printf("Héros: %s\n\n", ref);
				free(ref);
				ref = NULL;
			}
			else if (DEBUG)
				fprintf(stderr, "Problème récup ref carte: %d\n", check);

		}
		else
			printf("Il n'y a pas encore de héros\n\n");

		ref = NULL;

		for (i = 0; i < NB_ZONE; i++) {
			printf("Zone %s: ", i == 0? "de défense" : "d'attaque");

			for (j = 0; j < NB_EMPLACEMENT_ZONE; j++) { /* Affiche toutes les cartes dans la zone choisie auparavant */
				check = carte_get_ref(t->zone[j][i], &ref);
				printf("\t%s", check == 0? ref : "VIDE");

				free(ref);
				ref = NULL;
			}

			putchar('\n');
		}

		putchar('\n');
		printf("Zone des sorts: ");

		for (i = 0; i < NB_ZONE; i++) {
			check = carte_get_ref(t->sort[i], &ref);
			printf("\t%s", check == 0? ref : "VIDE");

			free(ref);
			ref = NULL;
		}

		printf("\n\n");
	}

	if (DEBUG)
		fprintf(stderr, "Fin affichage d'une terrain\n");
}

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
		if (carte_null(*c)) /* Si la carte n'est pas NULL, on doit la détruire pour ne pas avoir de fuite de mémoire */
			carte_detruire(c);

		int choix = -1, choix2 = -1;

		do {
			if (choix != -1)
				printf("Votre choix ne correspond pas à un choix possible, refaire la saisie.\n");

			printf("Veuillez choisir une zone pour y récupérer un personnage: \n1°) Défense\n2°) Attaque\n0°) Annuler\nVotre choix: ");
			scanf("%d", &choix);
		} while ((choix < 1 && choix > NB_ZONE) && choix != 0);

		if (choix) {
			int retour1 = 0, i = 0;
			char* ref1 = NULL;

			do {
				if (choix2 != -1)
					printf("Votre choix ne correspond pas à un choix possible, refaire la saisie.\n");

				printf("Veuillez choisir la carte à récupérer: \n");

				for (i = 0; i < NB_EMPLACEMENT_ZONE; i++) { /* Affiche toutes les cartes dans la zone choisie auparavant */
					retour1 = carte_get_ref(t->zone[i][choix - 1], &ref1);
					printf("\t%d°) %s", i + 1, retour1 == 0? ref1 : "VIDE");

					free(ref1);
					ref1 = NULL;
				}

				printf("\n0°) Annuler\nVotre choix: ");
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
		if (!carte_null(c)) {
			int choix = -1, choix2 = -1;

			do {
				if (choix != -1)
					printf("Votre choix ne correspond pas à un choix possible, refaire la saisie.\n");

				printf("Veuillez choisir une zone pour y poser le personnage: \n1°) Défense\n2°) Attaque\n0°) Annuler\nVotre choix: ");
				scanf("%d", &choix);
			} while ((choix < 1 && choix > NB_ZONE) && choix != 0);

			if (choix) {
				int retour1 = 0, i = 0;
				char* ref1 = NULL;

				do {
					if (choix2 != -1)
						printf("L'emplacement sélectionné est déjà occupé par un personnage, refaire la saisie\n");

					choix2 = -1;

					do {
						if (choix2 != -1)
							printf("Votre choix ne correspond pas à un choix possible, refaire la saisie.\n");

						printf("Veuillez choisir un emplacement vide pour y poser le personnage: \n");

						for (i = 0; i < NB_EMPLACEMENT_ZONE; i++) { /* Affiche toutes les cartes dans la zone choisie auparavant */
							retour1 = carte_get_ref(t->zone[i][choix - 1], &ref1);
							printf("\t%d°) %s", i + 1, retour1 == 0? ref1 : "VIDE");

							free(ref1);
							ref1 = NULL;
						}

						printf("\nVotre choix: ");
						scanf("%d", &choix2);
					} while ((choix2 < 1 || choix2 > NB_EMPLACEMENT_ZONE) && choix2 != 0); /* Tant que la saisie n'est pas bonne */
				} while (choix2 != 0 && !carte_null(t->zone[choix2 - 1][choix - 1])); /* Tant que la saisie est faite sur un emplacement déjà pris */

				if (choix2)
					t->zone[choix2 - 1][choix - 1] = c;
				else
					retour = 4; /* L'utilisateur a annulé le 2ème choix */
			}
			else
				retour = 3; /* L'utilisateur a annulé le 1er choix */
		}
		else
			retour = 2; /* Carte NULL */
	}
	else
		retour = 1; /* Terrain NULL */

	return retour;
}

int terrain_detruire(Terrain** t) {
	int retour = 0;

	if (!terrain_null(*t)) {
		if (!carte_null((*t)->heros))
			carte_detruire(&((*t)->heros));

		int i = 0, j = 0;

		for (i = 0; i < NB_ZONE; i++)
			for (j = 0; j < NB_EMPLACEMENT_ZONE; j++)
				if (!carte_null((*t)->zone[j][i]))
					carte_detruire(&((*t)->zone[j][i]));

		for (i = 0; i < NB_SORT; i++)
			if (!carte_null((*t)->sort[i]))
				carte_detruire(&((*t)->sort[i]));

		free(*t);
		*t = NULL;
	}
	else
		retour = 1;

	return retour;
}

int terrain_init(Terrain** t) {
	int retour = 0;

	if (!terrain_null(*t))
		terrain_detruire(t);

	if (((*t) = malloc(sizeof(Terrain))) != NULL) {
		(*t)->heros = NULL;
	}
	else
		retour = 1; /* Problème malloc */

	return retour;
}
