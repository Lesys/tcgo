/**
	\file joueur.c
	\brief Fichier de fonctions pour accesseurs et de modifications pour un Joueur
	\author WIDMER Alexis
	\version 1.0
	\date 05/03/2019

	Ce fichier permet d'avoir accès aux attributs d'un Joueur, de le créer ou de le supprimer.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/joueur.h"

int joueur_get_deck(Joueur* j, Pioche** deck) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!pipoche_null(*deck)
			pioche_detruire(deck);

		if (pioche_null(*deck))
			*deck = j->deck;
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int joueur_set_deck(Joueur* j, Pioche* deck) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!pipoche_null(j->deck)
			pioche_detruire(*(j->deck));

		if (pioche_null(j->deck))
			j->deck = deck;
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int joueur_get_main(Joueur* j, Pioche** hand) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!pipoche_null(*hand)
			pioche_detruire(hand);

		if (pioche_null(*hand))
			*hand = j->hand;
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int joueur_set_main(Joueur* j, Pioche* hand) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!pipoche_null(j->hand)
			pioche_detruire(*(j->hand));

		if (pioche_null(j->hand))
			j->hand = hand;
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int joueur_get_defausse(Joueur* j, Pioche** defausse) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!pipoche_null(*defausse)
			pioche_detruire(defausse);

		if (pioche_null(*defausse))
			*defausse = j->defausse;
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int joueur_set_defausse(Joueur* j, Pioche* defausse) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!pipoche_null(j->defausse)
			pioche_detruire(*(j->defausse));

		if (pioche_null(j->defausse))
			j->defausse = defausse;
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int joueur_get_terrain(Joueur* j, Terrain** terrain) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!pipoche_null(*terrain)
			terrain_detruire(terrain);

		if (terrain_null(*terrain))
			*terrain = j->terrain;
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

int joueur_set_terrain(Joueur* j, Terrain* terrain) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!pipoche_null(j->terrain)
			terrain_detruire(*(j->terrain));

		if (terrain_null(j->terrain))
			j->terrain = terrain;
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

/* Récupère le pseudo du joueur */
/**
	\fn int joueur_get_pseudo(Joueur* j, char** pseudo);
	\brief Permet de récupérer le pseudo d'un Joueur*

	\param j Le Joueur* dont on veut récupérer le pseudo
	\return Le code erreur s'il y en a un, sinon 0
*/
int joueur_get_pseudo(Joueur* j, char** pseudo) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (j->pseudo != NULL && strlen(j->pseudo) > 0) {
			if ((*pseudo) != NULL)
				free(*pseudo);

			(*pseudo) = malloc(sizeof(char) * (strlen(j->pseudo) + 1);

			if ((*pseudo) != NULL)
				strcpy(*pseudo, j->pseudo);
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

/**
	\fn int joueur_set_pseudo(Joueur* j, char* pseudo);
	\brief Permet de modifier le pseudo d'un Joueur*

	\param j Le Joueur* dont on veut remplacer le pseudo
	\return Le code erreur s'il y en a un, sinon 0
*/
int joueur_set_pseudo(Joueur* j, char* pseudo) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (pseudo != NULL && strlen(pseudo) > 0) {
			if ((j->pseudo) != NULL)
				free(j->pseudo);

			(j->pseudo) = malloc(sizeof(char) * (strlen(pseudo) + 1);

			if ((j->pseudo) != NULL)
				strcpy(j->pseudo, pseudo);
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

/* Récupère le score du joueur */
/**
	\fn int joueur_get_score(Joueur* j, int* score);
	\brief Permet de récupérer le score d'un Joueur*

	\param j Le Joueur* dont on veut récupérer le score
	\return Le score du Joueur*
*/
int joueur_get_score(Joueur* j, int* score) {
	int retour = 0;

	if (!joueur_null(j))
		*score = j->score;
	else
		retour = 1:

	return retour;
}

/**
	\fn int joueur_set_score(Joueur* j, int score);
	\brief Permet de récupérer le score d'un Joueur*

	\param j Le Joueur* dont on veut modifier le score
	\return Le score du Joueur*
*/
int joueur_set_score(Joueur* j, int score) {
	int retour = 0;

	if (!joueur_null(j))
		j->score = score;
	else
		retour = 1:

	return retour;
}

int joueur_get_type_joueur(Joueur* j, Type_Joueur* type) {
	int retour = 0;

	if (!joueur_null(j))
		*type = j->type;
	else
		retour = 1;

	return retour;
}


int joueur_set_type_joueur(Joueur* j, Type_Joueur type) {
	int retour = 0;

	if (!joueur_null(j))
		j->type = type;
	else
		retour = 1;

	return retour;
}


/* Récupère le joueur suivant */
/**
	\fn int joueur_get_suivant(Joueur* j, Joueur** suiv);
	\brief Permet de récupérer le prochain Joueur* à jouer

	\param j Le Joueur* dont on veut récupérer le Joueur suivant
	\return Code erreur
*/
int joueur_get_suivant(Joueur* j, Joueur** suiv) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!joueur_null(*suiv))
			joueur_detruire(suiv);

		if (joueur_null(*suiv))
			*suiv = j->suiv;
		else
			retour = 2; /* Problème lors de la destruction du joueur */
	}
	else
		retour = 1;

	return retour;
}

/**
	\fn int joueur_set_suivant(Joueur* j, Joueur* suiv);
	\brief Permet de récupérer le prochain Joueur* à jouer

	\param j Le Joueur* dont on veut récupérer le Joueur suivant
	\return Code erreur
*/
int joueur_set_suivant(Joueur* j, Joueur* suiv) {
	int retour = 0;

	if (!joueur_null(j)) {
		if (!joueur_null(suiv)) {
			if (!joueur_null(j->suiv))
				joueur_detruire(&(j->suiv));

			if (joueur_null(j->suiv))
				j->suiv = suiv;
			else
				retour = 3; /* Problème lors de la destruction du joueur */
		}
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

/**
	\fn int joueur_a_abandonne(Joueur* j);
	\brief Permet de savoir si le Joueur* a abandonné ou non

	\param j Le Joueur* dont on veut récupérer la valeur d'abandon
	\return VRAI si le Joueur* a abandonné, FAUX sinon
*/
int joueur_a_abandonne(Joueur* j) {
	return j->abandon;
}

/**
	\fn Joueur* joueur_abandonne(Joueur* j);
	\brief Fait abandonner un Joueur

	\param j Le Joueur* qu'on veut faire abandonner
*/
void joueur_abandonne(Joueur* j) {
	j->abandon = 1;
}

int joueur_get_sockfd(Joueur* j, int* sockfd) {
	int retour = 0;

	if (!joueur_null(j))
		*sockfd = j->sockfd;
	else
		retour = 1;

	return retour;
}

int joueur_set_sockfd(Joueur* j, int sockfd) {
	int retour = 0;

	if (!joueur_null(j))
		j->sockfd = sockfd;
	else
		retour = 1;

	return retour;
}


/*Joueur* joueur_copier(Joueur* j) {
	Joueur* j_copie = joueur_init(joueur_couleur(j));
	strcpy(j_copie->pseudo, j->pseudo);

	Piece* p_copie = liste_piece_copie(joueur_liste_piece(j));
*/
/*	j_copie->couleur = joueur_couleur(j);*/

/*	j_copie->type = joueur_type_joueur(j);*/
/*	j_copie->abandon = joueur_a_abandonne(j);

	return j_copie;
}*/

/* Vérifie qu'il y a un nombre correct de joueur */
/**
	\fn int verif_nb_joueur(int nb);
	\brief Vérifie si le nombre de joueur est correct (avec les variables en DEFINE)

	\param nb Le nombre de joueur saisi par l'utilisateur
	\return VRAI si le nombre de joueur saisi est correct, FAUX sinon
*/
int verif_nb_joueur(int nb) {
	return (nb >= NB_JOUEUR_MIN && nb <= NB_JOUEUR_MAX);
}

/* Alloue "nb_joueur" Joueurs, demande les pseudos et ajoute chaque joueur à la suite d'un autre. Retourne le 1er joueur créé (qui sera le joueur BLEU) */
/* Les paramètres optionnels seront le nombre de BOT ainsi que le nombre de joueurs en réseau (A FAIRE PLUS TARD) */
/**
	\fn Joueur* joueur_liste_creation(int nb_joueur, ...);
	\brief Crée la liste des Joueur en fonction du nombre passé en paramètre

	\param nb_joueur Le nomber de joueur qu'on souhaite créer
	\return Le premier Joueur* (les autres Joueur sont accessibles via joueur_get_suivant). NULL Si le nombre de joueur n'est pas correct.
*/
Joueur* joueur_liste_creation(int nb_joueur, ...) {

	if (!verif_nb_joueur(nb_joueur)) {
		printf("Le nombre de joueur ne correspond pas (%d au lieu d'être entre %d et %d)", nb_joueur, NB_JOUEUR_MIN, NB_JOUEUR_MAX);
		return NULL;
	}

	int i = 0;
	Joueur* first, *tmp;

	/* Création du premier joueur */
	first = joueur_init(c);
	first->suiv = first->prec = first;
	tmp = first;
	c++;

	/* Le premier joueur est créé, il ne faut donc pas le créer de nouveau. On commence à 1 */
	for (i = 1; i < nb_joueur; i++) {
		tmp->suiv = joueur_init(c);
		(tmp->suiv)->suiv = first;
		(tmp->suiv)->prec = tmp;

		tmp = tmp->suiv;
	}

	/* Attribue le 1er joueur en tant que suivant du dernier */
	first->prec = tmp;

	return first;
}

/* Fonction permettant de réinitialiser la liste de Joueur pour permettre de refaire une manche avec les mêmes pseudos */
/**
	\fn void joueur_liste_reinit(Joueur* j);
	\brief Réinitialise les Joueur (au début d'une manche par exemple) sans modifier le score

	\param j Le Joueur* qu'on veut réinisialiser (tous les Joueur sont réinitialisés)
*/
void joueur_liste_reinit(Joueur* j) {
	Joueur* first = j;

	/* Pour tous les Joueur */
	do {
		j->abandon = 0;

/*                liste_piece_detruire(&(j->liste_piece));

		j->liste_piece = piece_liste_creation();*/

		j = joueur_suivant(j);
	} while (first != j);
}

/* Crée un joueur. Les paramètres optionnels seront le type de joueur (LOCAL par défaut) */
/**
	\fn int joueur_init(Joueur** j)
	\brief Crée un Joueur en demandant le pseudo.

	\param Joueur** L'adresse de la variable du joueur initialisé
	\return code erreur
*/
int joueur_init(Joueur** j) {
	int retour = 0;

	if (!joueur_null(*j))
		joeuur_detruire(j);

	if (joueur_null(*j)) {
		*j = malloc(sizeof(Joueur));

		if (!joueur_null(*j)) {

			/* Permet d'avoir 15 caractères pour le pseudo + le caractère de fin de chaine */
			j->pseudo = malloc(sizeof(char) * (TAILLE_PSEUDO + 1));
			j->pseudo[0] = '\0';

			if (j->pseudo != NULL) {
				printf("Joueur %s, veuillez indiquer votre pseudo: ", couleur_tostring(c));
				scanf("%*[^\n]%*c", j->pseudo);
				scanf("%15s", j->pseudo);

				while (getchar() != '\n');

				/* Réalloue la bonne taille pour le pseudo */
				j->pseudo = realloc(j->pseudo, sizeof(char) * (strlen(j->pseudo) + 1));

				if (j->pseudo != NULL) {
					j->deck = NULL;

					j->hand = NULL;
					retour = pioche_init_vide(&(j->hand));

					if (!retour) {
						j->defausse = NULL;
						retour = pioche_init_vide(&(j->defausse));

						if (!retour) {
							j->terrain = NULL;
							retour = terrain_init(&(j->terrain));

							if (!retour) {
								j->type = LOCAL;
								j->suiv = NULL;
								j->prec = NULL;

								j->abandon = 0;
								j->score = 0;
				        			j->sockfd = 0;
							}
							else
								retour = 7; /* Problème initialisation du terrain */
						}
						else
							retour = 6; /* Problème initialisation de la défausse vide */
					}
					else
						reour = 5; /* Problème initialisation de la main vide */
				}
				else
					retour = 4; /* Problème realloc pseudo */
			}
			else
				retour = 3; /* Problème malloc pseudo */
		}
		else
			retour = 2; /* Problème malloc joueur */
	}
	else
		retour = 1; /*Joueur NULL après destruction */

	return retour;
}

/**
	\fn int joueur_null(Joueur* j);
	\brief Regarde si le Joueur existe ou non

	\param j Le Joueur* dont on veut savoir s'il existe ou non
	\return Renvoie VRAI si le Joueur n'existe pas (== est NULL), FAUX sinon
*/
int joueur_null(Joueur* j) {
	return (j == NULL);
}

/* Libère un Joueur */
/**
	\fn void joueur_free(Joueur** j);
	\brief Libère un joueur (et tous ses attributs)

	\param j L'adresse du Joueur* qu'on souhaite libérer
*/
void joueur_free(Joueur** j) {
	if (!joueur_null(*j)) {
		(*j)->suiv = NULL;
		(*j)->prec = NULL;

		if ((*j)->pseudo != NULL)
			free((*j)->pseudo);
		(*j)->pseudo = NULL;

		liste_piece_detruire(&((*j)->liste_piece));

		free(*j);
		(*j) = NULL;
	}
}

/*
	\fn Joueur* joueur_detruire(Joueur** j);
	\brief Détruit un Joueur

	\param j L'adresse du Joueur* qu'on souhaite détruire
	\return code erreur
*/
static int joueur_detruire(Joueur** j) {
	int retour = 0;

	Joueur* suiv = NULL;

	retour = pioche_detruire(&((*j)->deck));

	if (!retour) {
		retour = pioche_detruire(&((*j)->hand));

		if (!retour) {
			retour = pioche_detruire(&((*j)->defausse));

			if (!retour) {
				retour = terrain_detruire(&((*j)->terrain));

				if (!retour) {
					free((*j)->pseudo);

					if ((*j)->suiv != *j) /* S'il y a plus d'un joueur dans la boucle des joueurs */
						suiv = (*j)->suiv;
						/* Redéfini les joueurs suivants et précédents */
						suiv->prec = (*j)->prec;
						(*j)->prec->suiv = suiv;
					}

					joueur_free(*j);
					*j = NULL;
				}
				else
					retour = 4;
			 )
			else
				retour ) 3;
		}
		else
			retour = 2;
	}
	else
		retour = 1;

	return retour;
}

/* Détruit tous les joueurs */
/**
	\fn void joueur_liste_detruire(Joueur** j);
	\brief Détruit tous les Joueur

	\param j L'adresse du Joueur* qu'on souhaite détruire (détruit TOUS les Joueur)
*/
int joueur_liste_detruire(Joueur** j) {
	retour = 0;
	Joueur* tmp = NULL;

	while (!retour && !joueur_null(*j)) {
		retour = joueur_suivant(*j, &tmp);

		if (!retour) {
			retour = joueur_detruire(j);

			if (!retour)
				*j = tmp;
			else
				retour = 2;
		}
		else
			retour = 1;
	}

	return retour;
}

/* TODO */
int joueur_deck_vers_main(Joueur*);
int joueur_deck_vers_defausse(Joueur*);
int joueur_main_vers_deck(Joueur*);
int joueur_main_vers_defausse(Joueur*);
int joueur_defausse_vers_deck(Joueur*);
int joueur_defausse_vers_main(Joueur*);

