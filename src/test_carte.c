#include <stdio.h>
#include <stdlib.h>
#include "../include/carte.h"
#include "../include/chara.h"

int main() {
	Carte* cartes[4];
	int i;

	for (i = 0; i < 4; i++)
		cartes[i] = NULL;



	Chara* c1 = NULL;
	chara_init(&c1, CHARISME, 6, 6, 6);

	carte_init(&cartes[0], "Première carte", RIEN_EFFET, RIEN_UTILISATION, c1, "../ressources/c1.png", NULL);

	carte_afficher(cartes[0]);

	chara_afficher(cartes[0]->chara);

	Chara* c2 = NULL;
	chara_init(&c2, DETER, 9, 9, 9);

	carte_init(&cartes[1], "deuxième carte", RIEN_EFFET, RIEN_UTILISATION, c2, "../ressources/image1.png", cartes[0]);

	carte_afficher(cartes[1]);

	chara_afficher(cartes[1]->chara);

	Chara* c3 = NULL;
	chara_init(&c3, FORCE_DETER, 8, 8, 6);

	carte_init(&cartes[0], "Dernière carte", RIEN_EFFET, RIEN_UTILISATION, c3, "../ressources/image2.png", NULL);

	carte_afficher(cartes[0]);

	int retour;

	for (i = 0; i < 4; i++)
		if ((retour = carte_detruire(&cartes[i])) != 0)
			printf("Erreur lors de la desstruction: %d\n", retour);

	return 0;
}

