#include <stdio.h>
#include <stdlib.h>
#include "../include/terrain.h"

int main() {

	Terrain* t = NULL;

	int retour = terrain_init(&t);; /*pioche_init(&p, fichier);*/

	if (!retour) {
		fprintf(stderr, "Retour 0 (depuis main).\n");
		terrain_afficher(t);

		Carte* c = NULL;

		retour = carte_init(&c, "PD001", "test_nom", "test_anime", 0, RIEN_UTILISATION, NULL, "test_chemin", NULL);

		if (!retour) {
			fprintf(stderr, "\n====Carte créée:\n");
			carte_afficher(c);
		}
		else
			fprintf(stderr, "Problème carte_init: %d\n", retour);

		retour = terrain_set_heros(t, c);

		if (!retour) {
			fprintf(stderr, "On a bien ajouté le héros dans le terrain\n");
			terrain_afficher(t);
			fprintf(stderr, "\n\n");

			c = NULL;
			retour = carte_init(&c, "PD118", "test_nom", "test_anime", 0, RIEN_UTILISATION, NULL, "test_chemin", NULL);

			retour = terrain_poser_perso(t, c);
			if (!retour) {
				fprintf(stderr, "On a bien posé la carte\n");
				terrain_afficher(t);
			}
			else
				fprintf(stderr, "code retour: %d // problème pioche_remettre\n", retour);
		}
		else {
			fprintf(stderr, "code retour: %d // problème pioche_enlever\n", retour);
		}
	}
	else
		fprintf(stderr, "Il y a eu un problème dans l'initialisation du fichier (depuis main).\n");

	terrain_detruire(&t);

	return 0;
}

