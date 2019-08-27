#include <stdio.h>
#include <stdlib.h>
#include "../include/joueur.h"

int main() {
	Joueur* j1 = NULL, *j2 = NULL;
	int retour = 0;

	retour = joueur_init(&j1);

	if (!retour) {
		fprintf(stderr, "Joueur1 bien créé\n");

/*		retour = joueur_init(&j2);

		if (!retour) {
			fprintf(stderr, "Joueur2  bien créé\n");

			if (!retour) {
				fprintf(stderr, "Joueur bien détruits\n");
*/
				retour = joueur_liste_creation(2, &j1);

				if (!retour)
					fprintf(stderr, "Joueurs bien crées\n");
				else
					fprintf(stderr, "Problème joueur_liste_creation : %d\n", retour);
/*			}
			else
				fprintf(stderr, "Problème joueur_liste_detruire : %d\n", retour);

		}
		else
			fprintf(stderr, "Problème joueur_init j2: %d\n", retour);*/
	}
	else
		fprintf(stderr, "Problème joueur_init j1: %d\n", retour);

	retour = joueur_liste_detruire(&j1);

	if (!retour) {
		fprintf(stderr, "Joueur bien détruits\n");
	}
	else
		fprintf(stderr, "Problème joueur_liste_detruire : %d\n", retour);

	return 0;
}
