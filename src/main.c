// A ajouter à Zotero https://stackoverflow.com/questions/6127503/shuffle-array-in-c

#include "../include/gestion_cartes.h"
#include "../include/gestion_tableaux.h"
#include "../include/variables.h"
#include "../include/commun.h"

// Le but de ce programme est de faire des tableaux avec des numéros, mélangés, et des listes différentes
int main() {
	srand(time(NULL));

	int fini = 0;

        // Création des tableaux
        // Héros uniquement obtenables dans le HQ/QG
	int* heros_communs = NULL;

        // Héros obtenables dans les villes
        int* heros_rare_force = NULL;
        int* heros_rare_deter = NULL;
        int* heros_rare_chari = NULL;
        int* heros_epique_force = NULL;
        int* heros_epique_deter = NULL;
        int* heros_epique_chari = NULL;

        // Cartes chance, piège et vilains
        int* chances = NULL;
        int* pieges = NULL;
        int* vilains = NULL;

	// Déclaration du tableau contenant les pioches et leur quantité
	int* nb_cartes_pioches[NB_PIOCHE][2] = {{heros_communs, &NB_HEROS_COMMUNS}, {heros_rare_force, &NB_HEROS_RARES_FORCE}, {heros_rare_deter, &NB_HEROS_RARES_DETER}, {heros_rare_chari, &NB_HEROS_RARES_CHARI},
		{heros_epique_force, &NB_HEROS_EPIQUES_FORCE}, {heros_epique_deter, &NB_HEROS_EPIQUES_DETER}, {heros_epique_chari, &NB_HEROS_EPIQUES_CHARI}, {chances, &NB_CHANCES}, {pieges, &NB_PIEGES}, {vilains, &NB_VILAINS}};


	// Appelle du fichier permettant de remplir automatiquement le nombre de carte dans chaque pioche
	lecture_fichier(nb_cartes_pioches, FILENAME);

        int i = 0;

	// Allocation des pioches
	for (i = 0; i < NB_PIOCHE; i++) {
		if ((nb_cartes_pioches[i][0] = malloc(sizeof(*(nb_cartes_pioches[i][0])) * *(nb_cartes_pioches[i][1]))) == NULL) {
			printf("Allocation ratee pour la pioche %s\n\n", Pioches[i][0]);
			exit(1);
		}
	}
	// Ajout des numéros aléatoires
	remplissage_listes(nb_cartes_pioches);

//	afficher_tableau((nb_cartes_pioches[0][0]), *(nb_cartes_pioches[0][1]));

	// Mélange tous les tableaux
        for (i = 0; i < NB_PIOCHE; i++)
                shuffle(nb_cartes_pioches[i][0], *(nb_cartes_pioches[i][1]));

	// Affiche les pioches et les numéros dans l'ordre
        for (i = 0; i < NB_PIOCHE; i++)
                afficher_tableau(nb_cartes_pioches[i][0], *(nb_cartes_pioches[i][1]));

	// Boucle pour tirer les cartes
	while (!fini) {

		// Choix de l'utilisateur

		printf("Quel type de carte voulez-vous piocher?\n");

		for (i = 0; i < NB_PIOCHE; i++)
			printf("%s ) %s\n", Pioches[i][1], Pioches[i][0]);

		int choix = -1;

		printf("20 ) Piocher jusqu'a avoir un equipement\n");
		printf("0 ) Arreter le programme\nVotre choix: ");

		while ((choix < 1 || choix > NB_PIOCHE) && (choix != 0) && (choix != 20)) {
			if (choix != -1)
				printf("Veuillez choisir un choix entre 1 et %d\n", NB_PIOCHE);

			scanf("%d", &choix);
		}

		if (choix) {
			// Tire la carte de la pioche du joueur
			int carte = tirer_carte(nb_cartes_pioches, choix);

			switch (choix) {
				case 20: choix = trouver_pioche("chances") + 1;
//					choix = (int)Pioches[choix][1];
					break;
				default: break;
			}
			if (carte)
				printf("\n-------------------\nVous avez tire la carte %d de la pioche %s\n-------------------\n\n", carte, Pioches[choix - 1][0]);
			else
				printf("\n-------------------\nIl n'y a plus de carte dans le paquet %s\n-------------------\n\n", Pioches[choix - 1][0]);
		}
		else
			fini = 1;

	}

	// Libère toutes les pioches
	for (i = 0; i < NB_PIOCHE; i++)
		free(nb_cartes_pioches[i][0]);


	return 0;
}
