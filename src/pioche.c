#include <stdio.h>
#include <stdlib.h>

#include "../include/fonctions.h"
#include "../include/pioche.h"
#include "../include/carte.h"

void pioche_afficher(Pioche* p) {
	printf("Affichage de la Pioche:\n");

	Carte* c = NULL;
	Carte* tmp = NULL;
	int cmp = 1;

	int retour = pioche_get_sommet(p, &c);

	if (!retour) {
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

			} while (tmp->prec != NULL && !retour);

			pioche_set_sommet(p, c);
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
								fprintf(stderr, "%s & %s\n",  ref, ref2);
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

	return 0;
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

fprintf(stderr, "après tout: %d\n", retour);
			if (retour)
				pioche_detruire(p);
		}
		else /* Si le malloc n'a pas abouti */
			retour = 1;
	}

	return retour;
}

