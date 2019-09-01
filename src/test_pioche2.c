#include <stdio.h>
#include <stdlib.h>
#include "../include/carte.h"
#include "../include/stat.h"
#include "../include/pioche.h"

int main() {
	Pioche* p = NULL;

	int retour = creer_deck(&p);

	if (!retour) {
		fprintf(stderr, "Création OK, affichage\n\n");
		pioche_afficher(p);
	}
	else
		fprintf(stderr, "Création failed: %d\n\n", retour);

	pioche_detruire(&p);

	return 0;
}

