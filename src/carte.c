#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/carte.h"

void carte_afficher(Carte* carte) {
	Carte* prec;

	if (carte_null(carte))
		fprintf(stderr, "carte null\n");

	if (!carte_get_prec(carte, &prec)) {
		char* nom = NULL;
		int check;
		check = carte_get_nom(carte, &nom);

		if (!check) {
			printf("Carte actuelle: %s\n", nom);
			free(nom);
			nom = NULL;
		}

		if (!carte_null(prec)) {
			check = carte_get_nom(prec, &nom);

			if (!check) {
				printf("Carte précédente: %s\n", nom);
				free(nom);
				nom = NULL;
			}
		}
		else
			fprintf(stderr, "La carte précédente est NULL\n");

		chara_afficher(carte->chara);
	}
	else
		fprintf(stderr, "Affichage carte: Problème lors de la récupération de la carte précédente\n");
}

/*struct carte {
        char* nom_carte;
        Effet effet;
        Utilisation utilisation; 
        Chara* chara;
};
*/

int carte_null(Carte* c) {
	return (c == NULL);
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

int carte_get_chara(Carte* c, Chara** ch) {
	int retour = 0;

	if (!carte_null(c))
		*ch = c->chara;
	else
		retour = 1;

	return retour;
}

int carte_set_chara(Carte* c, Chara* ch) {
	int retour = 0;

	if (!carte_null(c))
		c->chara = ch;
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
				*chemin = c->chemin;
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

int carte_detruire(Carte** c) {
	int retour = 0;

	if (!carte_null(*c)) {
		if ((*c)->nom_carte != NULL)
			free((*c)->nom_carte);

		if ((*c)->chemin != NULL)
			free((*c)->chemin);

		if ((*c)->chara != NULL)
			chara_detruire(&((*c)->chara));

		free(*c);
		*c = NULL;
	}
	else
		retour = 1;

	return retour;
}

int carte_init(Carte** c, char* nom_carte, Effet effet, Utilisation utilisation, Chara* chara, char* chemin, Carte* prec) {
	int retour = 0;

	if (!carte_null(*c))
		carte_detruire(c);

	if (((*c) = malloc(sizeof(Carte))) != NULL) {
		(*c)->nom_carte = NULL;
		(*c)->chemin = NULL;
		(*c)->chara = NULL;
		(*c)->perso = NULL;
		(*c)->prec = NULL;
		(*c)->suiv = NULL;

		retour = carte_set_nom(*c, nom_carte);

		if (!retour) {
			retour = carte_set_effet(*c, effet);

			if (!retour) {
				retour = carte_set_utilisation(*c, utilisation);

				if (!retour) {
					retour = carte_set_chara(*c, chara);

					if (!retour) {
						retour = carte_set_chemin(*c, chemin);

						if (!retour)
							retour = carte_set_prec(*c, prec);
					}
				}
			}
		}

		if (retour)
			carte_detruire(c);
	}
	return retour;
}
