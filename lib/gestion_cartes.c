#include "../include/fonctions.h"

//
void choix_nombre_carte(int* nombre, char* phrase) {
        while (*nombre <= 0) {
                        printf("Combien y a-t-il de cartes %s: ", phrase);
                        scanf("%d", nombre);
                }
}

// Tire la 1ère carte de la liste et range la liste
int prendre_carte(int* liste_cartes, int nb_cartes, int debut) {

        // Récupère le numéro de la carte
        int carte = liste_cartes[debut];
	int i = debut;

        // Décale toutes les cartes de 1 cran vers la gauche du tableau
        for (i = debut + 1; i < nb_cartes && liste_cartes[i]; i++)
                liste_cartes[i - 1] = liste_cartes[i];

        // Ajoute un 0 à la fin du tableau
        liste_cartes[--i] = 0;

        // La dernière carte vient d'être piochée

        // Si carte == 0, alors il n'y a plus de carte dans cette pioche (== pioche vide)
        return carte;
}

int piocher_sans_defausse(int* nb_cartes_pioches[NB_PIOCHE][2], char* nom_pioche) {
	int num_pioche_chance = trouver_pioche(nom_pioche);
	int indice_carte = 0, choix = -1;

	int carte = (nb_cartes_pioches[num_pioche_chance][0])[indice_carte];
//	printf("\n\n-------------------\nPioche %s; carte n°%d\nContinuer de piocher?\n1°) Oui\n2°) Non\n", nom_pioche, carte);
//	scanf("%d", &choix);

	while (choix != 0 && choix != 1) {
		if (choix == -1)
			printf("\n\n-------------------\nPioche %s; carte n %d\nContinuer de piocher?\n1 ) Oui\n0 ) Non\n", nom_pioche, carte);
		else
			printf("\nVeuillez choisir entre 1 (Oui) et 0 (Non)\n");
		scanf("%d", &choix);
	}

	// Tant que l'utilisateur veut continuer et qu'il reste une carte à piocehr
	while (choix != 0 && indice_carte < *(nb_cartes_pioches[num_pioche_chance][1])) {

		// Si l'utilisateur décide de continuer
		if (choix == 1) {
			// Regarde la carte suivante et demande si elle est convenable
			carte = (nb_cartes_pioches[num_pioche_chance][0])[++indice_carte];
			printf("\n\n-------------------\nPioche %s; carte n %d\nContinuer de piocher?\n1 ) Oui\n0 ) Non\n", nom_pioche, carte);
		}
		else
			printf("\nVeuillez choisir entre 1 (Oui) et 0 (Non)\n");

		scanf("%d", &choix);
	}

	if (indice_carte < *(nb_cartes_pioches[num_pioche_chance][1]))
		carte = prendre_carte(nb_cartes_pioches[num_pioche_chance][0], *(nb_cartes_pioches[num_pioche_chance][1]), indice_carte);
	else
		printf("\n-------------------\nIl n'y a plus de cartes à piocher dans %s\n-------------------\n\n", nom_pioche);

	return carte;
}


// Permet de tirer une carte en fonction de la carte à tirer
int tirer_carte(int* nb_cartes_pioches[NB_PIOCHE][2], int choix) {

        int carte = 0;
        int chance = 0;

        // En fonction de la pioche choisie, un traitement différent s'oppère
        switch (choix) {
                case 1: /*int chance = rand() % 10;
                        // Rare à la palce de commune
                        if (chance == 1) {
                                chance = (rand() % 3) + 1;
                                carte = prendre_carte(nb_cartes_pioches[chance][0], *(nb_cartes_pioches[chance][1]));
                        }
                        else // Carte commune
                                carte = prendre_carte(nb_cartes_pioches[choix][0], *(nb_cartes_pioches[choix][1]));
                        break;*/
                case 2:
                case 3:
                case 4: chance = rand() % (PROB_AUGMENTATION_RARE_EPIQUE);
                        // Rang au dessus
                        if (chance == 1) {
                                printf("\n-------------------\nCHANCE!! La rarete de la carte passe a %s.\n", (choix == 1? "rare" : "epique"));
                                chance = (choix == 1? (rand() % 3) + (choix == 1? 1 : 4) : choix + 2);
                                printf("Type de la pioche: %s", (chance % 3 - 1 == 0? "Force" : (chance % 3 - 1 == 1? "Determination" : "Charisme")));
                                carte = prendre_carte(nb_cartes_pioches[chance][0], *(nb_cartes_pioches[chance][1]), 0);
                        }
                        else // Rang normal de la carte
                                carte = prendre_carte(nb_cartes_pioches[choix - 1][0], *(nb_cartes_pioches[choix - 1][1]), 0);
                        break;

                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10: carte = prendre_carte(nb_cartes_pioches[choix - 1][0], *(nb_cartes_pioches[choix - 1][1]), 0);
                        break;
		// Piocher jusqu'à avoir un équipement
		case 20: carte = piocher_sans_defausse(nb_cartes_pioches, "chances");
			choix = trouver_pioche("chances") + 1;
//			choix = (int)Pioches[choix][1];
			break;
                default: printf("Cette pioche n'existe pas\n\n");
                        break;
        }

        // Affiche si la pioche est vide
        if (!carte)
                printf("La pioche \"%s\" est vide\n\n", Pioches[choix - 1][0]);

        // Renvoie la carte sélectionnée
        return carte;
}

