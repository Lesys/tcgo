#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "../include/pioche.h"

static int recup_prochain_mot(char* chaine, int* pos, char** dest) {
	int retour = 0, nb_malloc = 5, cnt = 1;

	if (chaine != NULL && strlen(chaine) > 0) {
/*fprintf(stderr, "Avant free dans recup: %s\n", *dest);*/
		if (*dest != NULL)
			free(*dest);

		*dest = malloc(sizeof(char) * nb_malloc);
/*fprintf(stderr, "Après malloc dans recup: %s\n", *dest);*/
		if (*dest != NULL) {
			(*dest)[0] = '\0';
			while (chaine[*pos] != DELIMITEUR_CHAINE && chaine[*pos] != '\0') { /* Tant qu'on n'arrive pas à la fin du bout de chaine ou de ligne */
/*fprintf(stderr, "Avant if n° %d\n", cnt);*/
				if (cnt >= nb_malloc) { /* Si la place mémoire est trop petite pour accueillir toute l'information, on l'augmente */
					nb_malloc *= 2;
					*dest = realloc(*dest, nb_malloc);
				}
/*fprintf(stderr, "Après if n° %d\n", cnt);*/

				strncat(*dest, chaine + (*pos)++, 1); /* Copie du caractère à la fin de la chaine de destination */
				cnt++;
/*fprintf(stderr, "Après ajout: %s\n", *dest);*/
			}

/*			strcat(*dest, "\0"); // Fait automatiquement */
			*dest = realloc(*dest, strlen(*dest) + 1);
/*fprintf(stderr, "Fin recup_prochain_mot: %s\n", *dest);*/


/*			if (*pos != '\0')*/
			(*pos)++; /* Augmente d'1 cran pour ne pas rester sur le délimiteur */
		}
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

void pioche_afficher(Pioche* p) {
	if (DEBUG)
		fprintf(stderr, "Affichage de la Pioche:\n");

	Carte* c = NULL;
	Carte* tmp = NULL;
	int cmp = 1;

	int retour = pioche_get_sommet(p, &c); /* On récupère le sommet pour le remettre à la fin (pour empêcher les "pioche_depiler" d'enlever toute la pioche) */

	if (!retour) { /* Si on a bien récupéré le sommet et qu'il n'est pas NULL */
		if (c != NULL) {
			do {
				tmp = NULL;
				retour = pioche_depiler(p, &tmp);

				if (!retour) {
					printf("Carte %d : ", cmp++);
					carte_afficher(tmp);
				}
				else
					if (DEBUG)
						fprintf(stderr, "Problème pioche_depiler\n");

			} while (tmp->prec != NULL && !retour); /* Tant qu'on peut dépiler (== la prochaine carte (prec) n'est pas NULL) */

			pioche_set_sommet(p, c); /* On remet le sommet en place après avoir tout dépilé */
		}
		else
			printf("Cette pioche est vide\n");
	}
	else
		if (DEBUG)
			fprintf(stderr, "Problème récupération du sommet\n");
	if (DEBUG)
		fprintf(stderr, "Fin affichage Pioche\n");
}

int pioche_vide(Pioche* p) {
	return (p->sommet == NULL);
}

int pioche_null(Pioche* p) {
	return (p == NULL);
}

int pioche_limite_exemplaire(Pioche* p, Carte* c) {
	int retour = 0;

	if (!pioche_null(p)) {
		if (!pioche_vide(p)) {
			if (!carte_null(c)) {
				char* ref = NULL, *ref2 = NULL;

/*fprintf(stderr, "Avant get_ref\n");*/
				if (!carte_get_ref(c, &ref)) { /* Récupération de la référence de la carte recherchée */
/*fprintf(stderr, "Après get_ref: %s\n", ref);*/

					Carte* sommet = NULL;
					retour = pioche_depiler(p, &sommet); /* Récupération du sommet de la pile pour le remettre à la fin de la boucle */

					if (!retour) {
						retour = pioche_set_sommet(p, sommet); /* Remets le sommet */

						if (!retour) {
							Carte* c_temp = NULL;
							int compteur = 0;

							while (!retour && compteur < NB_EXEMPLAIRE_MAX && !pioche_vide(p) && !(retour = pioche_depiler(p, &c_temp))) { /* Tant qu'il y a une carte dans la pile non analysée et qu'on n'a pas atteint le maximum d'exemplaire de la carte */
								retour = carte_get_ref(c_temp, &ref2); /* Récupère la référence de la carte actuellement analysée */

								if (!retour) {
									/*fprintf(stderr, "%s & %s\n",  ref, ref2);*/
									compteur += strcmp(ref, ref2) == 0? 1 : 0; /* Si les deux chaines sont identiques (== même référence), ajoute un compteur */
								}

								c_temp = NULL; /* Il ne faut pas que la carte se fasse détruire lorsqu'on dépile à nouveau */
							}

							free(ref2);

							if (!retour) {
								retour = pioche_set_sommet(p, sommet);

								if (!retour) {
									if (compteur >= NB_EXEMPLAIRE_MAX) {
										if (DEBUG)
											fprintf(stderr, "Nombre d'exemplaire maximum de %s dans le deck atteint.\n", ref);
										retour = 8; /* Le nombre d'exemplaire maximum dans un deck pour cette carte a été atteint */
									}
								}
								else
									retour = 7; /* Problème MAJ sommet à la fin */
							}
							else
								retour = 6; /* Problème dans la boucle de recherche */

							free(ref);
						}
						else
							retour = 5; /* Problème MAJ sommet au début */
					}
					else
						retour = 4; /* Problème récupération sommet de la pile */
				}
				else
					retour = 3; /* Problème récupération de la référence de la carte cherchée */
			}
			else
				retour = 2; /* Carte à empiler NULL */
		}
		else
			retour = 0; /* Pioche vide (mais pas un problème) */
	}
	else
		retour = 1; /* Pioche NULL */


/*fprintf(stderr, "Retour limite exemplaire: %d\n", retour);*/
	return retour;
}

int pioche_empiler(Pioche* p, Carte* c) {
	int retour = 0;

	if (!pioche_null(p)) {
		if (!carte_null(c)) {
			if (!pioche_limite_exemplaire(p, c)) {
/*fprintf(stderr, "Ajout carte dans pioche\n");*/

				/* Affectation de l'ancien sommet au précédent du nouveau sommet + affectation du nouveau sommet */
				c->prec = p->sommet;
				p->sommet = c;
/*carte_afficher(p->sommet);*/

			}
			else {
/*fprintf(stderr, "Problème limite exemplaire\n");*/
				retour = 3; /* Le nombre maximum d'exemplaire de la carte est atteint OU un problème est survenu */
			}
		}
		else
			retour = 2; /* Carte à empiler NULL */
	}
	else
		retour = 1; /* Pioche NULL */

	return retour;
}

int pioche_depiler(Pioche* p, Carte** c) {
	int retour = 0;

	if (!pioche_null(p)) {
		if (!pioche_vide(p)) {
			if (!carte_null(*c))
				carte_detruire(c);

			if (pioche_get_sommet(p, c))
				retour = 3; /* La carte n'est pas utilisable depuis le paramètre (pour la fonction d'appel) */
			else /* Si tout s'est bien déroulé, on "enlève" la carte du dessus (elle existe toujours) */
				retour = carte_get_prec(p->sommet, &(p->sommet));
		}
		else
			retour = 2; /* Pioche VIDE */
	}
	else
		retour = 1; /* Pioche NULL */

	return retour;
}

int pioche_recup_carte_par_emplacement(Pioche* p, int emp, Carte** c) {
	int retour = 0;

	if (!pioche_null(p)) {
		if (!pioche_vide(p)) {
			if (emp >= 1) {
				int nb_carte = 0;

				retour = pioche_nb_carte(p, &nb_carte);

				if (!retour) {
					if (emp <= nb_carte) {
						if (!carte_null(*c))
							carte_detruire(c);

						retour = pioche_get_sommet(p, c);

						if (!retour) {
							int i = 1;

							for (i = 1; !retour && i < emp; i++)
								retour = carte_get_prec(*c, c);

							if (retour)
								retour = 7; /* Problème récupération prec */
						}
						else
							retour = 6; /* Problème récupération sommet */
					}
					else
						retour = 5; /* L'empalcement voulu est plus grand que le nombre de carte dans la pioche */
				}
				else
					retour = 4; /* Problème récupération nb carte dans la pioche */
			}
			else
				retour = 3; /* L'emplacement recherché n'est pas un nombre positif */
		}
		else
			retour = 2; /* Pioche vide, on ne peut donc pas récupérer la carte à l'emplacement donné */
	}
	else
		retour = 1; /* Pioche NULL */

	return retour;
}

int pioche_echanger_carte(Pioche* dest, Pioche* src) {
	int retour = 0;

	if (!pioche_null(dest)) {
		if (!pioche_null(src)) {
			if (!pioche_vide(src)) {
				char* nom = malloc(sizeof(char) * (TAILLE_REF + 1));
				Carte* c = NULL;

				printf("\n=====\nCHANGEMENT DE PIOCHE\n=====\nParmi les cartes suivantes, quelle carte transférer?\n");
				pioche_afficher(src);
				putchar('\n');

				do {
					if (retour)
						printf("\nLa référence saisie n'est pas présente dans la pioche. Veuillez saisir à nouveau: ");

					scanf("%s", nom);

				} while ((retour = pioche_enlever_par_ref(src, nom, &c)) == 3); /* Tant que la référence saisie n'est pas dans la pioche */

				free(nom);

				if (!retour) {
					retour = pioche_empiler(dest, c);

					if (retour) {
						if (DEBUG)
							fprintf(stderr, "Problème pioche_empiler dans dest: %d\n", retour);

						carte_detruire(&c);
					}
					else if (!retour) {
						printf("Carte échangée: ");
						carte_afficher(c);
					}
				}
				else if (retour && DEBUG)
					fprintf(stderr, "Problème pioche_enlever_par_ref dans src: %d\n", retour);
			}
			else {
				printf("La pioche source est vide, impossible d'y prendre une carte\n");
				retour = 3; /* Pioche src vide, impossible d'y prendre une carte */
			}
		}
		else
			retour = 2; /* src NULL */
	}
	else
		retour = 1; /* dest NULL */

	return retour;
}

int pioche_melanger(Pioche* p)
{
	int retour = 0;

	if (!pioche_null(p)) {
		if (!pioche_vide(p)) {
			int nb_carte = 0;

			retour = pioche_nb_carte(p, &nb_carte);

			if (!retour) {
				/* tmp: carte en dessous de c
				tmp2: carte en dessous de c_rnd
				c: carte à l'emplacement nb_carte - i
				c_rnd: carte à l'emplacement aléatoire entre 1 (sommet) et nb_carte - i - 1
				c_prec: carte au dessus de c
				c_rnd_prec: carte au dessus de c_rnd */
				Carte* tmp = NULL, *tmp2 = NULL, *c = NULL, *c_rnd = NULL, *c_prec = NULL, *c_rnd_prec = NULL;
				int i = 0, rnd = 0;
				srand(time(NULL));

				for (i = 0; !retour && i < nb_carte - 1; i++) {

					tmp = tmp2 = c = c_rnd = c_prec = c_rnd_prec = NULL;

					do {
						rnd = (rand() % (nb_carte - i - 1)) + 1; /* On prend la carte random (rnd entre 1 et nb_carte - i - 1) */
					} while (rnd == nb_carte - i); /* Normalement impossible */

					retour = pioche_recup_carte_par_emplacement(p, nb_carte - i - 1, &c_prec); /* Récupération de la carte à l'emplacement nb_carte - i */

					if (!retour) {
						if (rnd > 1)
							retour = pioche_recup_carte_par_emplacement(p, rnd - 1, &c_rnd_prec); /* Récupération de la carte à l'emplacement rnd - 1 */

						if (!retour) {
							retour = pioche_recup_carte_par_emplacement(p, nb_carte - i, &c); /* Récupération de la carte à l'emplacement nb_carte - i */

							if (!retour) {
								retour = pioche_recup_carte_par_emplacement(p, rnd, &c_rnd); /* Récupération de la carte à l'emplacement rnd */

								if (!retour) {
									retour = carte_get_prec(c, &tmp); /* Récupération de la carte en dessous de c */

									if (!retour) {
										retour = carte_get_prec(c_rnd, &tmp2); /* Récupération de la carte en dessous de rnd */

										if (!retour) {
											if (c != tmp2)
												retour = carte_set_prec(c, tmp2); /* Changement de la carte suivante de c par celle de rnd */
											else /* Cela veut dire que c_rnd est la carte au dessus de c */
												retour = carte_set_prec(c, c_rnd);

											if (!retour) {
												retour = carte_set_prec(c_rnd, tmp); /* Changement de la carte suivante de rnd par l'ancienne de c */

												if (!retour) {
													if (!carte_null(c_rnd_prec))
														retour = carte_set_prec(c_rnd_prec, c); /* Changement de la carte suivante de la précédente de rnd par c */
													else /* Si c_rnd_prec est NULL, c'est que la carte rnd est le sommet de la pioche */
														retour = pioche_set_sommet(p, c); /* On remplace le sommet de la pioche par la carte c */

													if (!retour) {
														if (c_rnd != c_prec) /* Si c_rnd n'est pas la carte au dessus de c (sinon, déjà fait au dessus) */
															retour = carte_set_prec(c_prec, c_rnd); /* Changement de l'ancienne carte suivante de la précédente de c par rnd */
													}
													else
														retour = 12;
												}
												else
													retour = 11;
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
							else
								retour = 6;
						}
						else
							retour = 5;
					}
					else
						retour = 4;

/*fprintf(stderr, "\n\n===========Emplacements desartes échangées: %d & %d\n\n", nb_carte - i, rnd); */
					if (DEBUG) {
						if (!retour)
							fprintf(stderr, "mélange %d fait sans problème\n", i);
						else
							fprintf(stderr, "mélange problème %d\n", retour);
					}

/*pioche_afficher(p);*/
				} /* Fin for */
			}
			else
				retour = 3; /* Problème récupération nombre de carte */
		}
		else
			retour = 2; /* Pioche vide */
	}
	else
		retour = 1; /* Pioche NULL */

	return retour;
}

int pioche_nb_carte(Pioche* p, int* nb_carte) {
	int retour = 0;

	if (!pioche_null(p)) {
		if (!pioche_vide(p)) {
			Carte* tmp = NULL;
			retour = pioche_get_sommet(p, &tmp); /* On récupère le sommet pour le remettre à la fin (pour empêcher les "pioche_depiler" d'enlever toute la pioche) */

			if (!retour) { /* Si on a bien récupéré le sommet*/
				*nb_carte = 1;

				while (!retour && tmp->prec != NULL) { /* Tant que la prochaine carte (prec) n'est pas NULL */
/*fprintf(stderr, "Avant get_prec:\n");
					carte_afficher(tmp);*/
					retour = carte_get_prec(tmp, &tmp);
/*fprintf(stderr, "Après get_prec:\n");
					carte_afficher(tmp);*/

					if (!retour)
						(*nb_carte)++;
					else
						retour = 3;
				}
			}
			else
				retour = 2; /* Problème récupération sommet */
		}
		else
			*nb_carte = 0; /* La pioche est vide */
	}
	else
		retour = 1; /* Pioche NULL */

	return retour;
}

int pioche_get_sommet(Pioche* p, Carte** sommet) {
	int retour = 0;

	if (!pioche_null(p)) {
		if (!pioche_vide(p))
			*sommet = p->sommet;
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int pioche_set_sommet(Pioche* p, Carte* sommet) {
	int retour = 0; /* Si retour != 0, c ne pourra pas être utilisé */

	/* Si la pioche est ni NULL, ni VIDE: On récupère la carte */

	if (!pioche_null(p))
		p->sommet = sommet;
	else
		retour = 1;

	return retour;
}

int pioche_ref_presente(Pioche* p, char* ref) {
	int retour = 0;
	char* ref2 = NULL;
	Carte* c = NULL, *tmp = NULL;

	pioche_get_sommet(p, &tmp);

	do {
		c = tmp;
		tmp = NULL;
		carte_get_prec(c, &tmp);
		carte_get_ref(c, &ref2);

		if (strcmp(ref, ref2) == 0) /* Si la référence est présente */
			retour = 1;

		free(ref2);
		ref2 = NULL;
	} while (!retour && !carte_null(tmp));

	return retour;
}

int pioche_enlever_par_ref(Pioche* p, char* ref, Carte** c) {
	int retour = 0;

	if (!pioche_null(p)) {
		Carte* sommet = NULL;
		retour = pioche_get_sommet(p, &sommet); /* On récupère le sommet pour le remettre à la fin (pour empêcher les "pioche_depiler" d'enlever toute la pioche) */

		if (!retour) { /* Si on a bien récupéré le sommet*/
			char* ref2 = NULL;
			int trouve = 0;
			Carte* tmp = sommet;
			Carte* prec = NULL, *tmp2 = NULL;

			do {
				if (!retour) {
					retour = carte_get_ref(tmp, &ref2);

					if (!retour)
						if (strcmp(ref, ref2) == 0) /* Si la référence de la carte correspond à celle qu'on cherche à enlever */
							trouve = 1;

				} else if (DEBUG)
					fprintf(stderr, "Problème pioche_depiler\n");

				if (!trouve) {
					prec = tmp;
					tmp = NULL;
					retour = carte_get_prec(prec, &tmp);
				}

			} while (!retour && !trouve && !carte_null(tmp)); /* Tant qu'on peut dépiler (== la prochaine carte (prec) n'est pas NULL) et qu'on n'a pas encore trouve la carte voulue*/

			free(ref2);
			ref2 = NULL;

			if (trouve) { /* Si on a trouvé la carte; on l'enlève et on la mets dans le paramètre */
				*c = tmp;

				if (tmp == sommet) { /* Si la carte à enlever est le sommet */
					retour = carte_get_prec(tmp, &tmp2);

					if (!retour)
						p->sommet = tmp2;
					else
						retour = 6;
				}
				else {
					retour = carte_get_prec(tmp, &tmp2);
/*fprintf(stderr, "retour carte_get_prec dans enlever_par_ref: %d\n", retour);*/

					if (!retour) {
						retour = carte_set_prec(prec, tmp2);

						if (retour)
							retour = 5;
					}
					else
						retour = 4;
				}
			}
			else
				retour = 3; /* La ref n'était pas dans la Pioche */
//			pioche_set_sommet(p, sommet); /* On remet le sommet en place après avoir tout dépilé */
		}
		else
			retour = 2; /* Problème récupération sommet */
	}
	else
		retour = 1; /* Pioche NULL */
/*fprintf(stderr, "retour pioche_enlever_par_ref: %d\n", retour);*/
	return retour;
}

int pioche_recup_par_ref(Pioche* p, char* ref, Carte** c) {
	int retour = 0;

	if (!pioche_null(p)) {
		Carte* sommet = NULL;
		retour = pioche_get_sommet(p, &sommet); /* On récupère le sommet pour le remettre à la fin (pour empêcher les "pioche_depiler" d'enlever toute la pioche) */

		if (!retour) { /* Si on a bien récupéré le sommet*/
			char* ref2 = NULL;
			int trouve = 0;
			Carte* tmp = sommet;
			Carte* prec = NULL;

			do {
				if (!retour) {
					retour = carte_get_ref(tmp, &ref2);

					if (!retour)
						if (strcmp(ref, ref2) == 0) /* Si la référence de la carte correspond à celle qu'on cherche à enlever */
							trouve = 1;

				} else if (DEBUG)
					fprintf(stderr, "Problème pioche_depiler\n");

				if (!trouve) {
					prec = tmp;
					tmp = NULL;
					retour = carte_get_prec(prec, &tmp);
				}

			} while (!retour && !trouve && !carte_null(tmp)); /* Tant qu'on peut dépiler (== la prochaine carte (prec) n'est pas NULL) et qu'on n'a pas encore trouve la carte voulue*/

			free(ref2);
			ref2 = NULL;

			if (trouve) /* Si on a trouvé la carte; on l'enlève et on la mets dans le paramètre */
				*c = tmp;
			else
				retour = 3; /* La ref n'était pas dans la Pioche */
		}
		else
			retour = 2; /* Problème récupération sommet */
	}
	else
		retour = 1; /* Pioche NULL */

	return retour;
}

int pioche_remettre(Pioche* p, Carte* c) {
	int retour = 0;

	if (!pioche_null(p)) {
		if (!carte_null(c)) {
			retour = pioche_empiler(p, c); /* Ajout de la carte dans la pioche */

			if (!retour) {
				int i = 0;

				for (i = 0; i <= 3 && !retour; i++) /* On mélange X fois */
					retour = pioche_melanger(p); /* Mélange de la pioche après avoir ajouté la carte */

				if (i <= 3 || retour)
					retour = 4; /* Problème lors du mélange */
			}
			else
				retour = 3; /* Problèeme empiler */
		}
		else
			retour = 2; /* Carte NULL */
	}
	else
		retour = 1; /* Pioche NULL */

	return retour;
}

int pioche_piocher_main_depart(Joueur* j) {
	int retour = 0, i;
	Pioche* main = NULL, *p = NULL;
	Carte* c = NULL;

	retour = joueur_get_deck(j, &p);

	if (!retour) {
		if (!pioche_vide(p)) {
			retour = pioche_init_vide(&main);

			if (!retour) {
				for (i = 0; !retour && i < NB_CARTE_DEPART; i++) { /* Récupération des NB_CARTE_DEPART cartes en haut de la pioche pour les mettre dans la main du joueur */
					retour = pioche_depiler(p, &c);
					if (!retour) {
						pioche_empiler(main, c);

						if (retour)
							retour = 5;
					}
					else
						retour = 4;
					c = NULL;
				}

				if (!retour) {
					retour = joueur_set_main(j, main);

					if (!retour) {
/*						retour = pioche_melanger(p);

						if (retour)
							retour = 8;
*/					}
					else
						retour = 7;
				}
				else
					retour = 6;
			}
			else
				retour = 3;
		}
		else
			retour = 2;
	}
	else
		retour = 1;
//TODO
	return retour;
}

int pioche_afficher_all_heros(Pioche** p) {

	fprintf(stderr, "On est dans afficher_all_héros\n");
	return 0;
}

int pioche_choisir_heros(Joueur* p) {
	int retour = 0;

	return retour;
}

int pioche_sauvegarder(Pioche* p) {
	int retour = 0;

	struct stat st = {0};

	if (!pioche_null(p)) {
		if (!pioche_vide(p)) {
			char* file_name = malloc(sizeof(char) * (TAILLE_NOM_FICHIER + strlen(DOSSIER_SAVE_FICHIER) + strlen(EXTENSION_SAVE_FICHIER) + 1));
			char* tmp = malloc(sizeof(char) * TAILLE_NOM_FICHIER);

			printf("Comment voulez-vous appeler le deck: ");
			scanf("%15s", tmp);

			strcpy(file_name, DOSSIER_SAVE_FICHIER);
			strcat(file_name, tmp);
			strcat(file_name, EXTENSION_SAVE_FICHIER);

			if (stat(DOSSIER_SAVE_FICHIER, &st) == -1) /* Crée le dossier de sauvegarde s'il n'existe pas */
				mkdir(DOSSIER_SAVE_FICHIER, 0700);

			FILE* f = fopen(file_name, "w");

			if (f != NULL) { /* Si le fichier s'est bien créé */
				free(file_name);
				free(tmp);

				Carte* c = NULL, *sommet = NULL;

				retour = pioche_get_sommet(p, &sommet);

				if (!retour) {
					char* ref = NULL;

					while (!retour && !pioche_vide(p)) { /* Tant qu'il y a une carte à sauvegarder */
						retour = pioche_depiler(p, &c);

						if (!retour) {
							retour = carte_get_ref(c, &ref); /* Récupération de la référence de la carte récupérée */

							if (!retour)
								fprintf(f, "%s\n", ref); /* Ecriture de la référence dans le fichier */
							else
								retour = 6;
						}
						else
							retour = 5;

						c = NULL;
					}
					if (ref != NULL)
						free(ref);

					retour = pioche_set_sommet(p, sommet);
				}
				else
					retour = 4; /* Problème récupération sommet */

				fclose(f);
			}
			else
				retour = 3; /* Problème création du fichier */
		}
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int pioche_charger(Pioche** p) {
	int retour = 0;

	struct stat st = {0};

	if (stat(DOSSIER_SAVE_FICHIER, &st) != -1) { /* Si le dossier de sauvegarde existe */
		if (!pioche_null(*p))
			pioche_detruire(p);

		if (pioche_null(*p)) {
			retour = pioche_init_vide(p);

			if (!retour) {
				char* file_name = malloc(sizeof(char) * (TAILLE_NOM_FICHIER + strlen(DOSSIER_SAVE_FICHIER) + strlen(EXTENSION_SAVE_FICHIER) + 1));
				char* tmp = malloc(sizeof(char) * TAILLE_NOM_FICHIER);

				printf("Saisissez le nom du deck que vous voulez charger: ");
				scanf("%15s", tmp);

				strcpy(file_name, DOSSIER_SAVE_FICHIER);
				strcat(file_name, tmp);
				strcat(file_name, EXTENSION_SAVE_FICHIER);

				FILE* f = fopen(file_name, "r");

				if (f != NULL) { /* Si le fichier s'est bien créé */
					free(file_name);
					free(tmp);

					Pioche* liste = NULL;
					Carte* c = NULL, *c2 = NULL;
					char* ref = malloc(sizeof(char) * (TAILLE_REF + 1));

					retour = pioche_init(&liste, 0, LISTE_CARTES_EMPLACEMENT);

					if (!retour) {
						while (!retour && fscanf(f, "%s\n", ref) != EOF) { /* Tant qu'il y a une carte à sauvegarder */
							if (pioche_ref_presente(liste, ref)) {
								retour = pioche_recup_par_ref(liste, ref, &c); /* Récupération des données de la carte */

								if (!retour) {
									retour = carte_copier(c, &c2); /* Copie de la carte */

									if (!retour)
										pioche_empiler(*p, c2); /* Ajout de la carte dans le deck */
								}
								else
									retour = 7;
							}
							else
								retour = 6;

							c = NULL;
							c2 = NULL;
						}
					}
					else
						retour = 5;

					pioche_detruire(&liste);
					free(ref);
					fclose(f);
				}
				else
					retour = 4; /* Problème création du fichier */
			}
			else
				retour = 3;
		}
		else
			retour = 2;
	}
	else
		retour = 1;

/*fprintf(stderr, "fin charger: %d\n", retour);*/

	return retour;
}

int creer_deck(Pioche** p) {
	int retour = 0;

	if (!pioche_null(*p))
		pioche_detruire(p);

	if (pioche_null(*p)) {
		retour = pioche_init_vide(p);

		if (!retour) {
			printf("Début de la création de deck\n\n");
			int choix = -1, nb = 0;
			char rep = '0', rep2;
			char* ref = NULL;
			Pioche* liste = NULL;
			Carte* c = NULL, *c2 = NULL;

			retour = pioche_init(&liste, 0, LISTE_CARTES_EMPLACEMENT); /* Récupération de toutes les cartes, effet etc */

			if (!retour) {
				do {
					choix = -1;
					rep = '0';

					do {
						if (choix != -1)
							printf("Veuillez faire un choix parmi les numéros proposés.\n\n");

						printf("\n1°) Ajouter une carte\n2°) Retirer une carte\n3°) Sauvegarder le deck\n4°) Charger un deck\n0°) Quitter\n\nVotre choix: ");
						scanf("%d", &choix);
					} while ((choix < 1 || choix > 4) && choix != 0);

					switch (choix) {
						case 1: retour = pioche_nb_carte(*p, &nb);

							if (!retour && nb < NB_DECK_MAX) {
								pioche_afficher(liste);
								ref = malloc(sizeof(char) * (TAILLE_REF + 1));

								if (ref != NULL) {
									printf("\nVeuillez choisir une carte à ajouter parmi les cartes ci-dessus (saisir la référence de la carte): ");
									scanf("%5s", ref);

									if (!pioche_ref_presente(liste, ref))
										printf("La référence %s n'existe pas, retour au menu précédent.\n", ref);
									else { /* Si la référence écrite est bien dans la liste des cartes */
										retour = pioche_recup_par_ref(liste, ref, &c);

										if (!retour) {
											retour = carte_copier(c, &c2);

											if (!retour)
												pioche_empiler(*p, c2);
										}

										c = NULL;
										c2 = NULL;
									}

									free(ref);
								}
							}
							else
								printf("Vous ne pouvez plus ajouter de cartes dans votre deck, retour au menu précédent.\n");

							break;

						case 2: if (!pioche_vide(*p)) {
								pioche_afficher(*p);
								ref = malloc(sizeof(char) * (TAILLE_REF + 1));

								if (ref != NULL) {
									printf("\nVeuillez choisir une carte à retirer parmi les cartes ci-dessus (saisir la référence de la carte): ");
									scanf("%5s", ref);

									if (!pioche_ref_presente(*p, ref))
										printf("La carte %s n'est pas dans votre deck, retour au menu précédent.\n", ref);
									else { /* Si la référence écrite est bien dans le deck des cartes */
										retour = pioche_enlever_par_ref(*p, ref, &c);

										if (!retour)
											carte_detruire(&c);

										c = NULL;
									}

									free(ref);
								}
							}
							else
								printf("Votre deck est vide, vous ne pouvez pas retirer de carte, retour au menu précédent.\n");

							break;

						case 3: retour = pioche_sauvegarder(*p);

							if (retour) {
								printf("Erreur lors de la sauvegarde, annulation de la sauvegarde\n");
								retour = 0;
							}
							break;

						case 4: do {
								while((rep2 = getchar()) != EOF && rep2 != '\n');

								if (rep != '0' && rep != '\n')
									printf("'%c' n'est pas un choix possible. Veuillez saisir un choix parmi O, o, N ou n.\n\n", rep);

								printf("Si vous continuez, le deck actuel sera remplacé. Continuer? O/o - N/n\n\nVotre choix: ");
								scanf("%c", &rep);

							} while (rep != 'O' && rep != 'o' && rep != 'N' && rep != 'n');

							if (rep == 'O' || rep == 'o')
								retour = pioche_charger(p);

							if (retour == 1) { /* Si le dossier n'est pas créé */
								printf("Le dossier de sauvegarde n'existe pas (vous n'avez pas encore fait de sauvegarde de deck). Chargement impossible.\n");
								retour = 0;
							}
							break;

						case 0: do {
								while((rep2 = getchar()) != EOF && rep2 != '\n');

								if (rep != '0' && rep != '\n')
									printf("'%c' n'est pas un choix possible. Veuillez saisir un choix parmi O, o, N ou n.\n\n", rep);

								printf("Voulez-vous sauvegarder le deck avant de quitter? O/o - N/n\n\nVotre choix: ");
								scanf("%c", &rep);
							} while (rep != 'O' && rep != 'o' && rep != 'N' && rep != 'n');

							if (rep == 'O' || rep == 'o')
								retour = pioche_sauvegarder(*p);

							if (retour)
								retour = 4;
							break;

						default: break;
					}

/*fprintf(stderr, "Problème dans le while: %d\n", retour);*/
				} while (!retour && choix != 0);

				if (!retour && choix == 0)
					printf("Création de deck terminée\n\n");

				if (retour)
					retour = 4; /* Problème dans le while */

				pioche_detruire(&liste);
			}
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

int pioche_detruire(Pioche** p) {
	int retour = 0;

	if (!pioche_null(*p)) {
		Carte* c = NULL;

		/* Destruction de toutes les cartes tant qu'il n'y a pas d'erreur */
/*		while (!carte_null((*p)->carte) && retour == 0) {
			retour = carte_get_prec((*p)->carte, &c);

			if (retour == 0) {
				retour = detruire_carte(&((*p)->carte));

				if (retour == 0)
					(*p)->carte = c;
			}
		}
*/

		/* Tant que la fonction ne retourne pas d'erreur */
		while (!pioche_vide(*p) && (retour = pioche_depiler(*p, &c)) == 0/* && !carte_null(c)*/) {
			carte_detruire(&c);
		}

		/* Si la pioche a bien été vidée */
		if (pioche_vide(*p)) {
			if (DEBUG)
				fprintf(stderr, "pioche vidée\n");
			free(*p);
			*p = NULL;
		}
		else
			retour = 2; /* La pioche n'a pas été vidée entièrement */
	}
	else
		retour = 1; /* Pioche NULL */


	if (DEBUG && retour)
		fprintf(stderr, "Erreur pioche_detruire: %d\n", retour);

	return retour;
}

int pioche_init(Pioche** p, int nb_limite_carte, char* file_name) {
	int retour = 0;

	/* Détruit la pioche pour la refaire si elle n'est pas NULL */
	if (!pioche_null(*p))
		retour = pioche_detruire(p);

	/* Si la destruction s'est bien passée (si elle a été faite) */
	if (!retour) {
		if (!pioche_null((*p) = malloc(sizeof(**p)))) {
			retour = pioche_set_sommet(*p, NULL);

			if (!retour) { /* Pas de problème lors de l'initialisation du sommet */
				if (file_name != NULL) {
					FILE* f;

					if (DEBUG)
						fprintf(stderr, "nom fichier: %s.\n", file_name);

					/* Si le fichier n'a pas de problème d'ouverture */
					if ((f = fopen(file_name, "r")) != NULL) {
						char* chaine = NULL, *ref = NULL, *type_carte = NULL, *nom = NULL, *nom_anime = NULL, *atk = NULL, *hp = NULL, *cout = NULL, *effet = NULL, *chemin = NULL;
						chaine = malloc(sizeof(*chaine) * 300); /* Alloue 300 caractères pour la chaine */

						int cnt = 0, i = 0;

						if (nb_limite_carte == 0)
							cnt = -1;

						Carte* c = NULL;

						while (!retour && fscanf(f, "%[^\n]\n", chaine) != EOF && cnt < nb_limite_carte) { /* Tant qu'il y a une ligne à lire et qu'on n'a pas atteint la limite de carte de la pioche */
/*fprintf(stderr, "chaine à traiter: %s\n", chaine);*/
							if (chaine[0] != '#') { /* Si ce n'est pas une ligne commentaire */
								c = NULL;
								i = 0;

								recup_prochain_mot(chaine, &i, &ref);
								recup_prochain_mot(chaine, &i, &type_carte);
								recup_prochain_mot(chaine, &i, &nom);
								recup_prochain_mot(chaine, &i, &nom_anime);
								recup_prochain_mot(chaine, &i, &atk);
								recup_prochain_mot(chaine, &i, &hp);
								recup_prochain_mot(chaine, &i, &cout);
								recup_prochain_mot(chaine, &i, &effet);

								chemin = malloc(sizeof(char) * strlen(ref) + 5); /* 5 pour l'extension .png et \0 */
								strcpy(chemin, ref);
								strcat(chemin, EXTENSION_CARTE);

								Stat stat;
								stat_init(&stat, *hp != NO_STAT? atoi(hp) : HP_NULL, *atk != NO_STAT? atoi(atk) : ATTAQUE_NULL);

								/* Crée une carte avec les valeurs de la ligne */
								/* TODO Créer une variable Stat qui prend l'atk et les hp */
								retour = carte_init(&c, ref, nom, nom_anime, *cout != NO_STAT? atoi(cout) : COUT_NULL, RIEN_UTILISATION, stat, chemin, NULL);

								if (!retour) { /* Si la carte a bien été créée, l'ajoute à la pioche */
									retour = pioche_empiler(*p, c);

									if (retour == 3) { /* Si la carte ajoutée est déjà en 3 exemplaire, le code retour est 3. On laisse passé (non bloquant) */
										retour = 0;
										carte_detruire(&c); /* On détruit la carte qu'on vient de créer puisqu'elle ne sera plus accessible sinon (pas dans la pioche) */
									}
								}
								else
									if (DEBUG)
										fprintf(stderr, "Carte %d non créée.\n", cnt);

								if (!retour && cnt >= 0)
									cnt++;

								free(ref); ref = NULL;
								free(type_carte); type_carte = NULL;
								free(nom); nom = NULL;
								free(nom_anime); nom_anime = NULL;
								free(atk); atk = NULL;
								free(hp); hp = NULL;
								free(cout); cout = NULL;
								free(effet); effet = NULL;
								free(chemin); chemin = NULL;
							}
						}

						if (DEBUG)
							fprintf(stderr, "Nb cartes créées: %d\n", cnt);

						free(chaine);
						chaine = NULL;

						if (!retour) {
							/*retour = pioche_melanger(*p);*/

							if (retour)
								retour = 2; /* Problème mélange */
						}
					}
					else {
						if (DEBUG)
							fprintf(stderr, "Le fichier %s n'a pas réussi à s'ouvrir.\n", file_name);
						retour = 1;
					}

					fclose(f);
				}
				else
					if (DEBUG)
						fprintf(stderr, "Pas de nom de fichier, la pioche est créée avec un sommet NULL");
			}

			if (retour)
				pioche_detruire(p);
		}
		else /* Si le malloc n'a pas abouti */
			retour = 1;
	}


	return retour;
}

/* Initialisation d'une pioche vide (comme la main ou la défausse au début d'une partie) */
int pioche_init_vide(Pioche** p) {
	int retour = 0;

	/* Détruit la pioche pour la refaire si elle n'est pas NULL */
	if (!pioche_null(*p))
		retour = pioche_detruire(p);

	/* Si la destruction s'est bien passée (si elle a été faite) */
	if (!retour) {
		if (!pioche_null((*p) = malloc(sizeof(**p)))) {
			retour = pioche_set_sommet(*p, NULL);

			if (retour)
				retour = 3;
		}
		else
			retour = 2;
	}
	else
		retour = 1; /* Pioche non NULL */

	return retour;
}
