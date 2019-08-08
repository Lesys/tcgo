#include "../include/gestion_tableaux.h"
#include "../include/commun.h"

// Adapte les noms (remplace les underscore "_" par des espaces " ")
static void rename_liste(char* chaine) {
	chaine--;
	while (*(++chaine))
		*chaine = *chaine == '_'? ' ' : *chaine;
}

// Permet de récupérer le numéro avec un nom de pioche
int trouver_pioche(char* nom_pioche) {
	int num_pioche = 0;

	/* Tant qu'on n'a pas dépassé la limite du nombre de pioche et qu'on n'a pas trouvé le correspondance */
	while (num_pioche < NB_PIOCHE && strcmp(nom_pioche, Pioches[num_pioche][0]))
		num_pioche++;

	return num_pioche;
}

// Permet de lire la lsite de paramètres pour ne pas à avoir les rentrer à chaque nouvelle partie
void lecture_fichier(int* nb_cartes_pioches[NB_PIOCHE][2], char* filename) {
	FILE* file = 0;
	char ligne[30];
//	printf("nom fichier: %s\n\n", filename);

	if ((file = fopen("../include/liste.txt", "r"))) {
		int num_pioche = 0, nb_cartes = 0;

//		printf("Début de la lecture:\n\n");

		// Lecture de toutes les lignes dans le fichier
		while (fscanf(file, "%s %d\n", ligne, &nb_cartes) != EOF){
			// Renomme la ligne pour correspondre au tableau de pioche
			rename_liste(ligne);
//			printf("Lecture ligne: %s(fin)\n\n", ligne);

			num_pioche = trouver_pioche(ligne);

			// Si une chaine correspond, affiche laquelle
			if (num_pioche >= NB_PIOCHE) {
				printf("Le nom ne correspond a rien dans la pioche\n\n");
				exit(1);
			}
			else {
//				printf("La ligne %s correspond à %s\n\n", ligne, Pioches[num_pioche][0]);

//				while (++i < taille)
//					nb_cartes = nb_cartes * 10 + ligne[i] - '0';

				printf("Il y a %d cartes\n\n", nb_cartes);

//				printf("Ajoute %d cartes dans la pioche %s\n\n", nb_cartes, Pioches[num_pioche][0]);

				// Ajoute le nombre de cartes dans la pioche correspondante
				*(nb_cartes_pioches[num_pioche][1]) = nb_cartes;
			}
		}

		fclose(file);
//		printf("fin de la lecture dans la fonction\n\n");
	}
	else
		printf("Fichier non ouvert\n\n");

}

// Permet de remplir les listes avec les numéros de toutes les cartes de chaque catégorie
void remplissage_listes(int* nb_cartes_pioches[NB_PIOCHE][2]) {

        int i = 0, j = 0;
        // Permet de parcourir toutes les pioches
        for (i = 0; i < NB_PIOCHE; i++) {
//		printf("Pioche n° %d:\n", i + 1);
                // Parcour la pioche en cours pour ajouter les numéros
                for (j = 1; j <= *(nb_cartes_pioches[i][1]); j++) {
                        // Ajoute les numéros de 1 à X dans le tableau correspondant
//			printf("Ajout du numéro %d\n", j);
                        *((nb_cartes_pioches[i][0]) + j - 1) = j;
                }
        }
}

// Permet d'afficher une pioche
void afficher_tableau(int* pioche, int nb_cartes) {
        int i = 0;
        for (i = 0; i < nb_cartes; i++)
                printf("Carte %d: %d\n", i + 1, pioche[i]);

        printf("\n\n");
}

// Mélange les éléments d'un tableau
void shuffle(int* pioche, int nb_cartes)
{
        if (nb_cartes > 1)
        {
                int i;
                for (i = 0; i < nb_cartes - 1; i++)
                {
                        int j = i + rand() / (RAND_MAX / (nb_cartes - i) + 1);
                        int t = pioche[j];
                        pioche[j] = pioche[i];
                        pioche[i] = t;
                }
        }
}

