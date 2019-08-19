/*#include "../include/joueur.h"*/
#include "../include/pioche.h"
#include <stdio.h>
#include <stdlib.h>

#define NB_CHOIX 8

int main(int argc, char** argv) {
	int choix = -1, retour = 0;

	printf("====================\n\n\t\tDébut du jeu:\n\n");

	Pioche* deck = NULL, *hand = NULL, *defausse = NULL;

	retour = pioche_init(&hand, NULL);

	if (!retour) { /* Initialisation de la main et de la défausse (vides) */
		retour = pioche_init(&defausse, NULL);

		if (retour && DEBUG)
			fprintf(stderr, "Problème initialisation defausse NULL: %d\n", retour);
	}
	else if (DEBUG)
		fprintf(stderr, "Problème initialisation main NULL: %d\n", retour);

	while (choix != 0) { /* Tant que l'utilisateur ne quitte pas */
		choix = -1;

		printf("====================\n\nVotre main:\n");
		pioche_afficher(hand);
		printf("\n\n====================\n\n");

		printf("1°) Piocher\n2°) Ajouter une carte du deck à la main\n");
		printf("3°) Envoyer une carte de la main à la défausse\n4°) Envoyer une carte du deck à la défausse\n");
		printf("5°) Remettre une carte de la main au deck\n6°) Remettre une carte de la défausse au deck\n7°) Récupérer une carte de la défausse à la main\n");
		printf("8°) Initialiser la pioche\n0°) Quitter\n\n");
		printf("Votre choix: ");

                while ((choix < 1 || choix > NB_CHOIX) && (choix != 0)) { /* Tant qu'il ne fait pas un choix possible */
                        if (choix != -1)
                                printf("Veuillez choisir un choix entre 1 et %d (ou 0)\n", NB_CHOIX);

                        scanf("%d", &choix);
                }

		if (choix != 8 && choix != 0 && pioche_null(deck)) /* Si le deck n'est pas initialisé et qu'on veut intéragir avec, on l'empêche */
			printf("Veuillez initialiser le deck avant de faire cette action\n");
		else {
			Carte* c = NULL;
			char* nom_fichier = NULL, *tmp = NULL;

			switch (choix) {
				case 1: retour = pioche_depiler(deck, &c);

					if (!retour) {
						retour = pioche_empiler(hand, c);

						if (retour && DEBUG) {
							fprintf(stderr, "Problème pioche_empiler dans main: %d\n", retour);
							carte_detruire(&c);
						}
						else if (!retour) {
							printf("Vous avez pioché la carte ");
							carte_afficher(c);
						}
					}
					else if (retour == 2)
						printf("\nVous n'avez plus de carte dans votre deck\n");
					else if (retour && DEBUG)
						fprintf(stderr, "Problème pioche_depiler: %d\n", retour);

					c = NULL;
					break;

				case 2:
					break;

				case 3:
					break;

				case 8:	nom_fichier = malloc(sizeof(char) * 100);
					tmp = malloc(sizeof(char) * 100);
					strcpy(nom_fichier, "../include/");

					printf("Indiquez le nom du fichier à charger (doit se trouver dans le dossier 'include' du projet): ");
					scanf("%s", tmp);

					strcat(nom_fichier, tmp);
					retour = pioche_init(&deck, nom_fichier);

					if (pioche_null(deck) && DEBUG)
						fprintf(stderr, "Pioche non initialisée\n");
					else
						fprintf(stderr, "Pioche initialisée\n");

					free(nom_fichier);
					free(tmp);
					break;

				case 0: break;

				default: printf("Ce choix n'existe pas / n'est pas encore traité\n");
					break;
			}
		}
	}

	pioche_detruire(&deck);
	pioche_detruire(&hand);
	pioche_detruire(&defausse);

	return 0;
}
