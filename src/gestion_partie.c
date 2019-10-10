#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/gestion_partie.h"

int lancer_une_partie() {
	int retour = 0;
	int i = 0;

	Joueur* joueur = NULL, *j_tmp = NULL;
/*	Pioche* liste = NULL;*/

	retour = joueur_liste_creation(NB_JOUEUR_MAX, &joueur);

	if(!retour) {
		fprintf(stderr, "Joueurs créés\n");
		Pioche* p = NULL;
		char* pseudo = NULL;

		for (i = 1; !retour && i <= NB_JOUEUR_MAX; i++) { /* Choix du deck et du héros pour chaque joueur */
			retour = joueur_get_pseudo(joueur, &pseudo);

			if (!retour) {
				p = NULL;

				printf("Joueur %d (%s):\n", i, pseudo);
				do {
					if (retour == 4)
						printf("Le deck que vous avez saisi n'existe pas (faites attention à la casse).\n");

					retour = pioche_charger(&p); /* Choix du deck (possible création) des joueurs */
				} while (retour == 4);

				if (!retour) {
					retour = pioche_melanger(p); /* Mélange de la pioche avant de la mettre au joueur */

					if (!retour) {
						retour = joueur_set_deck(joueur, p); /* Ajout du deck au joueur */

						if (!retour) {
							retour = pioche_choisir_heros(joueur); /* Choix du héros du joueur */ /* TODO */

							if (!retour) {
								retour = joueur_get_suivant(joueur, &j_tmp);

								if (!retour) {
									joueur = j_tmp;
									j_tmp = NULL;
								}
								else
									retour = 6;
							}
							else
								retour = 5;
						}
						else
							retour = 4;
					}
					else
						retour = 3;
				}
				else
					retour = 2;
			}

			if (pseudo != NULL)
				free(pseudo);
			pseudo = NULL;
		}
	}
	else
		retour = 1;

	if (!retour) { /* S'il n'y a pas eu de problème dans la configuration des joueurs */
		for (i = 1; !retour && i <= NB_JOUEUR_MAX; i++) {
		retour = pioche_piocher_main_depart(joueur);

		if (!retour) {
			Pioche* deck = NULL, *hand = NULL;
			retour = joueur_get_deck(joueur, &deck);

			if (!retour) {
				pioche_afficher(deck);

				retour = joueur_get_main(joueur, &hand);

				if (!retour) {
					pioche_afficher(hand);

					retour = joueur_get_suivant(joueur, &j_tmp);

					if (!retour) {
						joueur = j_tmp;
						j_tmp = NULL;
					}
					else
						retour = 10;
				}
				else
					retour = 9;
			}
			else
				retour = 8;
		}
		else
			retour = 7;
		}
	}

	joueur_liste_detruire(&joueur);

	return retour;
}

int menu() {
	int retour = 0;
	int choix = -1;
	char buf[10];
	Pioche* p = NULL;

	printf("Bienvenue sur le jeu du TCGO du serveur Mini-jeux Manga/Animes.\n\n");

	do {
		choix = -1;

		do {
			if (choix != -1)
				printf("Veuillez choisir un choix entre les propositions possibles\n\n");

			printf("Que souhaitez-vous faire?\n");
			printf("1°) Faire un duel\n2°) Edition de deck\n0°) Quitter\n\nVotre choix: ");
			scanf("%s", buf);

			if (!isdigit(*buf)) {
				choix = -2;
//				while (getchar() != '\n');
			}
			else
				choix = atoi(buf);

		} while ((choix < 1 || choix > 2) && choix != 0);

		switch (choix) {
			case 1: retour = lancer_une_partie();
				break;

			case 2: retour = creer_deck(&p);
				pioche_detruire(&p);

				if (retour == 1) {
					printf("Vous n'avez pas encore enregistré de deck pour le moment, vous ne pouvez donc pas charger de deck.\n");
					retour = 0;
				}
				else if (retour == 4) {
					printf("Le deck que vous avez saisi n'existe pas (faites attention à la casse).\n");
					retour = 0;
				}
				break;

			default: break;
		}
	} while (choix != 0 && !retour);

	if (retour)
		printf("Un problème est survenu, veuillez consulter le développeur. Code erreur: %d\n", retour);
	else
		printf("Le programme est terminé, merci d'avoir joué! À bientôt.\n\n");

	return retour;
}
