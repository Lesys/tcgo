#include <stdio.h>
#include <stdlib.h>
#include "../include/carte.h"
#include "../include/stat.h"
#include "../include/pioche.h"

int main() {

	char* fichier = "../../include/liste.txt";

	Pioche* p = NULL;

	int retour = pioche_init(&p, fichier);

	if (retour == 0) {
		fprintf(stderr, "Retour 0 (depuis main).\n");
/*		pioche_afficher(p);*/

/*		int nb_carte;*/
		Carte* c2 = NULL;

		retour = pioche_recup_carte_par_emplacement(p, 18, &c2);

		if (!retour) {
			fprintf(stderr, "\n====Carte récupérée:\n");
			carte_afficher(c2);
		}
		else
			fprintf(stderr, "Problème recup_carte: %d\n", retour);

		Carte* c = NULL;
		retour = pioche_enlever_par_ref(p, "PD120", &c);

		if (!retour) {
			fprintf(stderr, "On a bien enlevé la carte\n");
			carte_afficher(c);
			fprintf(stderr, "\n\n");
/*			pioche_afficher(p);*/

			retour = pioche_remettre(p, c);
			if (!retour) {
				fprintf(stderr, "On a bien remis la carte\n");
				pioche_afficher(p);
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


	pioche_detruire(&p);

	return 0;
/*	Carte* cartes[4];
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

	carte_init(&cartes[1], "deuxième carte", RIEN_EFFET, RIEN_UTILISATION, c2, "../ressources/image1.png", NULL);

	carte_afficher(cartes[1]);

	chara_afficher(cartes[1]->chara);

	Chara* c3 = NULL;
	chara_init(&c3, FORCE_DETER, 8, 8, 6);

	carte_init(&cartes[0], "Dernière carte", RIEN_EFFET, RIEN_UTILISATION, c3, "../ressources/image2.png", NULL);

	carte_afficher(cartes[0]);

	Pioche* p = NULL;

	if (pioche_init(&p, COMMUN))
		fprintf(stderr, "Il y a eu une erreur\n");

	pioche_empiler(p, cartes[0]);
	pioche_afficher(p);
	pioche_empiler(p, cartes[1]);

	pioche_afficher(p);

	pioche_detruire(&p);
*/
//	int retour;

/*	for (i = 0; i < 4; i++)
		carte_detruire(&cartes[i]);
			printf("Erreur lors de la desstruction: %d\n", retour);
*/
	return 0;
}

