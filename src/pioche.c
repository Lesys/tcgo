#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/fonctions.h"
#include "../include/pioche.h"
#include "../include/carte.h"

void pioche_afficher(Pioche* p) {
	printf("Affichage de la Pioche:\n");

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
					printf("Problème pioche_depiler\n");

			} while (tmp->prec != NULL && !retour); /* Tant qu'on peut dépiler (== la prochaine carte (prec) n'est pas NULL) */

			pioche_set_sommet(p, c); /* On remet le sommet en place après avoir tout dépilé */
		}
		else {
			printf("Sommet NULL\n");
		}
	}
	else
		printf("Problème récupération du sommet\n");

	printf("Fin affichage Pioche\n");
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

if (!retour)
	fprintf(stderr, "mélange %d fait sans problème\n", i);
else
	fprintf(stderr, "mélange problème %d\n", retour);

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

int pioche_enlever(Pioche* p, char* ref, Carte** c) {
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
				prec = tmp;
				tmp = NULL;
				retour = carte_get_prec(prec, &tmp);

				if (!retour) {
					retour = carte_get_ref(tmp, &ref2);

					if (!retour)
						if (strcmp(ref, ref2) == 0) /* Si la référence de la carte correspond à celle qu'on cherche à enlever */
							trouve = 1;

				} else
					printf("Problème pioche_depiler\n");

			} while (!retour && !trouve && tmp->prec != NULL); /* Tant qu'on peut dépiler (== la prochaine carte (prec) n'est pas NULL) et qu'on n'a pas encore trouve la carte voulue*/

			if (trouve) { /* Si on a trouvé la carte; on l'enlève et on la mets dans le paramètre */
				*c = tmp;
				retour = carte_set_prec(prec, tmp->prec);

				if (retour)
					retour = 4;
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
		while ((retour = pioche_depiler(*p, &c)) == 0 && !carte_null(c)) {
			carte_detruire(&c);
		}

		/* Si la pioche a bien été vidée */
		if (pioche_vide(*p)) {
			fprintf(stderr, "pioche vidée\n");
			free(*p);
			*p = NULL;
		}
		else
			retour = 2; /* La pioche n'a pas été vidée entièrement */
	}

	return retour;
}

int pioche_init(Pioche** p, char* file_name) {
	int retour = 0;

	/* Détruit la pioche pour la refaire si elle n'est pas NULL */
	if (!pioche_null(*p))
		retour = pioche_detruire(p);

	/* Si la destruction s'est bien passée (si elle a été faite) */
	if (!retour) {
		if (!pioche_null((*p) = malloc(sizeof(**p)))) {
			retour = pioche_set_sommet(*p, NULL);

/*fprintf(stderr, "après sommet: %d\n", retour);*/
			if (!retour) { /* Pas de problème lors de l'initialisation du sommet */
				FILE* f;

				fprintf(stderr, "nom fichier: %s.\n", file_name);

				/* Si le fichier n'a pas de problème d'ouverture */
				if ((f = fopen(file_name, "r")) != NULL) {
					char* chaine = NULL;
					chaine = malloc(sizeof(*chaine) * 100); /* Alloue 100 caractères pour la chaine */
/*char* test_chaine = NULL;*/
					int cnt = 0;
					while (!retour && fscanf(f, "%[^\n]\n", chaine) != EOF) { /* Tant qu'il y a une ligne à lire */
						Carte* c = NULL;

						/* Crée une carte avec les valeurs de la ligne */
						retour = carte_init(&c, chaine, "test_nom", "test_anime", 0, RIEN_UTILISATION, NULL, "test_chemin", NULL);

/*fprintf(stderr, "affichage ref chaine: %s\n", chaine);
fprintf(stderr, "affichage ref de c: %s\n", c->ref);

carte_get_ref(c, &test_chaine);
fprintf(stderr, "affichage ref get_ref: %s\n", test_chaine);*/

						if (!retour) { /* Si la carte a bien été créée, l'ajoute à la pioche */
/*fprintf(stderr, "avant empiler\n");*/
							retour = pioche_empiler(*p, c);

							if (retour == 3) /* Si la carte ajoutée est déjà en 3 exemplaire, le code retour est 3. On laisse passé (non bloquant) */
								retour = 0;
						}
						else
							fprintf(stderr, "Carte %d non créée.\n", cnt);

						cnt++;
					}

					fprintf(stderr, "Nb cartes créées: %d\n", cnt);

					free(chaine);
				}
				else {
					fprintf(stderr, "Le fichier %s n'a pas réussi à s'ouvrir.\n", file_name);
					retour = 1;
				}

				fclose(f);

			}

/*fprintf(stderr, "après tout: %d\n", retour);*/
			if (retour)
				pioche_detruire(p);
		}
		else /* Si le malloc n'a pas abouti */
			retour = 1;
	}

	return retour;
}

