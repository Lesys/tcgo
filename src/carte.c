#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/carte.h"
#include "../include/fonctions.h"

void carte_afficher(Carte* carte) {
	if (DEBUG)
		fprintf(stderr, "Affichage d'une carte\n");

	Carte* prec = NULL;

	if (carte_null(carte) && DEBUG)
		fprintf(stderr, "carte null\n");
	else { /*if (!carte_get_prec(carte, &prec)) {*/
		char* chaine = NULL;
		int check = carte_get_ref(carte, &chaine);
		int cout;
		Stat stat;

		printf("\n\n");

		if (!check) {
			if (DEBUG)
				fprintf(stderr, "Carte actuelle:\n\n");

			printf("Référence: %s\n", chaine);
			if (chaine != NULL)
				free(chaine);
			chaine = NULL;

		}

		check = carte_get_nom(carte, &chaine);

		if (!check) {
			printf("Nom: %s\n", chaine);
			if (chaine != NULL)
				free(chaine);
			chaine = NULL;
		}

		check = carte_get_nom_anime(carte, &chaine);

		if (!check) {
			printf("Nom de l'animé: %s\n", chaine);
			if (chaine != NULL)
				free(chaine);
			chaine = NULL;
		}

		check = carte_get_cout(carte, &cout);

		if (!check) {
			printf("Cout: ");
			if (cout != -1)
				printf("%d\n", cout);
			else
				printf("Aucun\n");
		}

		check = carte_get_stat(carte, &stat);

		if (!check)
			stat_afficher(stat);


/*		check = carte_get_chemin(carte, &chaine);

		if (!check) {
			printf("CHemin de l'image: %s\n", chaine);
			free(chaine);
			chaine = NULL;
		}
*/
		check = carte_get_prec(carte, &prec);

		if (check && DEBUG)
			fprintf(stderr, "Affichage carte: Problème lors de la récupération de la carte précédente\n");
		else if (!carte_null(prec)) {
			check = carte_get_ref(prec, &chaine);

			if (!check) {
				if (DEBUG)
					fprintf(stderr, "Carte précédente: %s\n", chaine);

				if (chaine != NULL)
					free(chaine);
				chaine = NULL;
			}
		}
		else
			if (DEBUG)
				fprintf(stderr, "La carte précédente est NULL\n");

/*		stat_afficher(carte->stat);*/
	}

	putchar('\n');

	if (DEBUG)
		fprintf(stderr, "Fin affichage d'une carte\n");
}

/*struct carte {
        char* nom_carte;
        Effet effet;
        Utilisation utilisation; 
        Stat* stat;
};
*/

int carte_null(Carte* c) {
	return (c == NULL);
}

int carte_get_ref(Carte* c, char** ref) {
	int retour = 0;

	if (!carte_null(c)) {
		if (c->ref != NULL && strlen(c->ref) > 0) {
			if ((*ref) != NULL)
				free(*ref);

			(*ref) = malloc(sizeof(char) * (strlen(c->ref) + 1));

			if ((*ref) != NULL)
				strcpy(*ref, c->ref);
			else
				retour = 3;
		}
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int carte_set_ref(Carte* c, char* ref) {
	int retour = 0;

	if (!carte_null(c))
		/* Si le nom à donner n'est pas "corrompu" (non NULL et contient au moins un caractère) */
		if (ref != NULL && strlen(ref) > 0) {
			if (c->ref != NULL)
				free(c->ref);

			c->ref = malloc(sizeof(char) * (strlen(ref) + 1));

			if (c->ref != NULL)
				strcpy(c->ref, ref);
			else
				retour = 3;
		}
		else
			retour = 2;
	else
		retour = 1;

	return retour;
}

int carte_get_nom(Carte* c, char** nom) {
	int retour = 0;

	if (!carte_null(c)) {
		if (c->nom_carte != NULL && strlen(c->nom_carte) > 0) {
			if ((*nom) != NULL)
				free(*nom);

			(*nom) = malloc(sizeof(char) * (strlen(c->nom_carte) + 1));

			if ((*nom) != NULL)
				strcpy(*nom, c->nom_carte);
			else
				retour = 3;
		}
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int carte_set_nom(Carte* c, char* nom) {
	int retour = 0;

	if (!carte_null(c))
		/* Si le nom à donner n'est pas "corrompu" (non NULL et contient au moins un caractère) */
		if (nom != NULL && strlen(nom) > 0) {
			if (c->nom_carte != NULL)
				free(c->nom_carte);

			c->nom_carte = malloc(sizeof(char) * (strlen(nom) + 1));

			if (c->nom_carte != NULL)
				strcpy(c->nom_carte, nom);
			else
				retour = 3;
		}
		else
			retour = 2;
	else
		retour = 1;

	return retour;
}

int carte_get_nom_anime(Carte* c, char** nom_anime) {
	int retour = 0;

	if (!carte_null(c)) {
		if (c->nom_anime != NULL && strlen(c->nom_anime) > 0) {
			if ((*nom_anime) != NULL)
				free(*nom_anime);

			(*nom_anime) = malloc(sizeof(char) * (strlen(c->nom_anime) + 1));

			if ((*nom_anime) != NULL)
				strcpy(*nom_anime, c->nom_anime);
			else
				retour = 3;
		}
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int carte_set_nom_anime(Carte* c, char* nom_anime) {
	int retour = 0;

	if (!carte_null(c))
		/* Si le nom_anime à donner n'est pas "corrompu" (non NULL et contient au moins un caractère) */
		if (nom_anime != NULL && strlen(nom_anime) > 0) {
			if (c->nom_anime != NULL)
				free(c->nom_anime);

			c->nom_anime = malloc(sizeof(char) * (strlen(nom_anime) + 1));

			if (c->nom_anime != NULL)
				strcpy(c->nom_anime, nom_anime);
			else
				retour = 3;
		}
		else
			retour = 2;
	else
		retour = 1;

	return retour;
}

int carte_get_cout(Carte* c, int* cout) {
	int retour = 0;

	if (!carte_null(c))
		*cout = c->cout;
	else
		retour = 1;

	return retour;
}

int carte_set_cout(Carte* c, int cout) {
	int retour = 0;

	if (!carte_null(c))
		c->cout = cout;
	else
		retour = 1;

	return retour;
}

int carte_get_prec(Carte* c, Carte** prec) {
	int retour = 0;

	if (!carte_null(c))
		*prec = c->prec;
	else
		retour = 1;

	return retour;
}

int carte_set_prec(Carte* c, Carte* prec) {
	int retour = 0;

	if (!carte_null(c))
		c->prec = prec;
	else
		retour = 1;

	return retour;
}

int carte_get_effet(Carte* c, Effet* e) {
	int retour = 0;

	if (!carte_null(c))
		*e = c->effet;
	else
		retour = 1;

	return retour;
}

int carte_set_effet(Carte* c, Effet e) {
	int retour = 0;

	if (!carte_null(c))
		c->effet = e;
	else
		retour = 1;

	return retour;
}

int carte_get_utilisation(Carte* c, Utilisation* u) {
	int retour = 0;

	if (!carte_null(c))
		*u = c->utilisation;
	else
		retour = 1;

	return retour;
}

int carte_set_utilisation(Carte* c, Utilisation u) {
	int retour = 0;

	if (!carte_null(c))
		c->utilisation = u;
	else
		retour = 1;

	return retour;
}

int carte_get_stat(Carte* c, Stat* ch) {
	int retour = 0;

	if (!carte_null(c)) {
		retour = stat_copie(ch, c->stat);

		if (retour)
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int carte_set_stat(Carte* c, Stat ch) {
	int retour = 0;

	if (!carte_null(c)) {
		retour = stat_copie(&(c->stat), ch);

		if (retour)
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int carte_get_chemin(Carte* c, char** chemin) {
	int retour = 0;

	if (!carte_null(c))
		if (c->chemin != NULL) {
			if ((*chemin) != NULL)
				free(*chemin);

			(*chemin) = malloc(sizeof(char) * (strlen(c->chemin) + 1));

			if ((*chemin) != NULL)
				strcpy(*chemin, c->chemin);
			else
				retour = 3;
		}
		else
			retour = 2;
	else
		retour = 1;

	return retour;
}

int carte_set_chemin(Carte* c, char* chemin) {
	int retour = 0;

	if (!carte_null(c))
		if (chemin != NULL && strlen(chemin) > 0) {
			if (c->chemin != NULL)
				free(c->chemin);

			c->chemin = malloc(sizeof(char) * (strlen(chemin) + 1));

			if (c->chemin != NULL)
				strcpy(c->chemin, chemin);
			else
				retour = 3;
		}
		else
			retour = 2;
	else
		retour = 1;

	return retour;
}

int carte_copier(Carte* src, Carte** copie) {
	int retour = 0;

	if (!carte_null(src)) {
		char* ref = src->ref, *nom_carte = src->nom_carte, *nom_anime = src->nom_anime, *chemin = src->chemin;
		int cout = src->cout;
		Utilisation utilisation = src->utilisation;
		Stat stat = src->stat;

		retour = carte_init(copie, ref, nom_carte, nom_anime, cout, utilisation, stat, chemin, NULL);

		if (retour)
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int carte_detruire(Carte** c) {
	int retour = 0;

	if (!carte_null(*c)) {
		if ((*c)->ref != NULL)
			free((*c)->ref);

		if ((*c)->nom_carte != NULL)
			free((*c)->nom_carte);

		if ((*c)->nom_anime != NULL)
			free((*c)->nom_anime);

		if ((*c)->chemin != NULL)
			free((*c)->chemin);

		free(*c);
		*c = NULL;
	}
	else
		retour = 1;

	return retour;
}

int carte_init(Carte** c, char* ref, char* nom_carte, char* nom_anime, int cout/*, Effet effet*/, Utilisation utilisation, Stat stat, char* chemin, Carte* prec) {
	int retour = 0;

	if (!carte_null(*c))
		carte_detruire(c);

	if (((*c) = malloc(sizeof(Carte))) != NULL) {
		(*c)->ref = NULL;
		(*c)->nom_anime = NULL;
		(*c)->nom_carte = NULL;
		(*c)->chemin = NULL;
/*		(*c)->stat = NULL;*/
		(*c)->prec = NULL;
		(*c)->suiv = NULL;

		retour = carte_set_ref(*c, ref);

		if (!retour) {
			retour = carte_set_nom(*c, nom_carte);

			if (!retour) {
				retour = carte_set_nom_anime(*c, nom_anime);

				if (!retour) {
					retour = carte_set_cout(*c, cout);

					if (!retour) {
						retour = carte_set_utilisation(*c, utilisation);

						if (!retour) {
							retour = carte_set_stat(*c, stat);

							if (!retour) {
								retour = carte_set_chemin(*c, chemin);

								if (!retour) {
									retour = carte_set_prec(*c, prec);

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
						retour = 5; /* Problème set cout */
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
			carte_detruire(c);
	}
	else
		retour = 1; /* Problème malloc */

	return retour;
}
