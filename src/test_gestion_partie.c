#include <stdio.h>
#include <stdlib.h>
#include "../include/gestion_partie.h"

int main() {
	int retour = 0;

	retour = menu();

	if (!retour) {
		fprintf(stderr, "Tout s'est bien passé dans le menu.\n");
	}
	else
		fprintf(stderr, "Problème dans le menu: %d\n", retour);

	return 0;
}
