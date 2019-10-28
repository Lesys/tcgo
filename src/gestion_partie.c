#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/gestion_partie.h"

// Renvoie vrai si la partie est finie, faux sinon
int partie_finie(Joueur* j) {
	int i = 0, fini = 0;
	Joueur* suiv = NULL;

	for (i = 1; !fini && i <= NB_JOUEUR_MAX; i++) {
		fini = joueur_a_abandonne(j);

		joueur_get_suivant(j, &suiv);
		j = suiv;
		suiv = NULL;
	}

	return fini;
}

// Crée un terrain vide et y place les héros (pour chaque joueur), continue le jeu jusqu'à ce qu'un joueur perde son héros
int lancer_une_partie(Joueur* j) {
	int retour = 0, i = 0;

	Carte* heros = NULL;
	Terrain* t = NULL;
	Joueur* suiv = NULL;

	for (i = 1; !retour && i <= NB_JOUEUR_MAX; i++) {
//joueur_afficher(j);
//		retour = terrain_init(&t);

//		if (!retour) {
		retour = joueur_get_heros(j, &heros);

		if (!retour) {
//fprintf(stderr, "affichage héros dans lancer_une_partie\n");
//carte_afficher(heros);
//				retour = terrain_set_heros(t, heros);

//				if (!retour) {
			retour = joueur_get_terrain(j, &t);

			if (!retour) {
				terrain_afficher(t);
				retour = joueur_get_suivant(j, &suiv);

				if (!retour) {
					j = suiv;
					suiv = NULL;
					t = NULL;
					heros = NULL;
				}
				else
					retour = 3;
			}
			else
				retour =  2;
/*				}
				else
					retour = 3;
			}
			else
				retour = 2;
*/		}
		else
			retour = 1;
	}

	if (!retour) { // Si on a bien initialisé les terrains
		while (!retour && !partie_finie(j)) {
			retour = joueur_get_terrain(j, &t);

			if (!retour) {
				terrain_afficher(t);

				joueur_afficher_main(j);

				if (getchar() == 'q') // Temporisation TODO (jouer la partie)
					joueur_abandonne(j);

				t = NULL;

				retour = joueur_get_suivant(j, &suiv);

				if (!retour) {
					j = suiv;
					suiv = NULL;
				}
				else
					retour = 7;
			}
			else
				retour = 6;
		}

		if (!retour) {
			char* pseudo = NULL;
			suiv = NULL;

			if (joueur_a_abandonne(j)) {
				retour = joueur_get_suivant(j, &suiv);

				if (!retour)
					j = suiv;
			}

			if (!retour)
				retour = joueur_get_pseudo(j, &pseudo);

				if (!retour)
					printf("Le gagnant est le joueur %s\n", pseudo);
		}
		else
			retour = 5;
	}
	else
		retour = 4;

	return retour;
}

int debuter_une_partie() {
	int retour = 0;
	int i = 0;

	Joueur* joueur = NULL, *j_tmp = NULL;
/*	Pioche* liste = NULL;*/

	retour = joueur_liste_creation(NB_JOUEUR_MAX, &joueur);

	if(!retour) {
		fprintf(stderr, "Joueurs créés\n");
		Pioche* p = NULL;
		char* pseudo = NULL;
		int nb_cartes = 0;

		for (i = 1; !retour && i <= NB_JOUEUR_MAX; i++) { /* Choix du deck et du héros pour chaque joueur */
			retour = joueur_get_pseudo(joueur, &pseudo);

			if (!retour) {
				p = NULL;

				printf("Joueur %d (%s):\n", i, pseudo);
				do {
					if (retour == 4)
						printf("Le deck que vous avez saisi n'existe pas (faites attention à la casse).\n");

					retour = pioche_charger(&p); /* Choix du deck (possible création) des joueurs */

					if (!retour) {
						retour = pioche_nb_carte(p, &nb_cartes);

						if (!retour && nb_cartes != NB_DECK_MAX) {
							printf("Il n'y a pas assez de cartes dans le deck sélectionné (il faut %d cartes pour faire un deck jouable, actuellement: %d)\n", NB_DECK_MAX, nb_cartes);
							retour = 1;
						}
					}
					fprintf(stderr, "retour: %d\n", retour);
				} while ((!retour && nb_cartes != NB_DECK_MAX) || retour);// || retour == 4);

				if (!retour) {
					Carte* heros = NULL;
					retour = pioche_recup_heros(p, &heros);

					if (!retour) {
						if (carte_null(heros)) { // Aucun héros présent, demande à ajouter un héros
							printf("Il n'y a pas de héros dans ce deck, veuillez choisir un héros.\n");
							retour = pioche_choisir_heros(&p);

							if (!retour) {
								retour = pioche_recup_heros(p, &heros);

								if (retour)
									retour = 10;
							}
							else
								retour = 9;
						}

fprintf(stderr, "héros: \n");
carte_afficher(heros);
						if (!retour) { // Si la récup du héros s'est bien passée
							retour = pioche_melanger(p); /* Mélange de la pioche avant de la mettre au joueur */

							if (!retour) {
								retour = joueur_set_deck(joueur, p); /* Ajout du deck au joueur */

								if (!retour) {
	//								retour = pioche_choisir_heros(&p); /* Choix du héros du joueur */ /* TODO */
									retour = joueur_set_heros(joueur, heros);

									if (!retour) {
										retour = joueur_get_suivant(joueur, &j_tmp);

										if (!retour) {
											joueur = j_tmp;
											j_tmp = NULL;
										}
										else
											retour = 8;
									}
									else
										retour = 7;
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
		} // Fin for
	}
	else
		retour = 1;

	if (!retour) { /* S'il n'y a pas eu de problème dans la configuration des joueurs */
		for (i = 1; !retour && i <= NB_JOUEUR_MAX; i++) {
//fprintf(stderr, "Main joueur %d: \n", i);
//pioche_afficher(joueur->deck);
			retour = pioche_piocher_main_depart(joueur);

			if (!retour) {
				Pioche* deck = NULL, *hand = NULL;
				retour = joueur_get_deck(joueur, &deck);

				if (!retour) {
//					pioche_afficher(deck);

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

		if (!retour) { // Si tous s'est bien passé, on lance le jeu
			retour = lancer_une_partie(joueur);
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
			case 1: retour = debuter_une_partie();
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
