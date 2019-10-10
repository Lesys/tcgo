#include <stdio.h>
#include <stdlib.h>
#include "../include/stat.h"

void stat_afficher(Stat stat) {

	printf("Stats: \n");
	printf("\tHP: ");
	if (stat.hp != -1)
		printf("%d\n", stat.hp);
	else
		printf("Aucun\n");

	printf("\tAttaque: ");
	if (stat.attaque != -1)
		printf("%d\n", stat.attaque);
	else
		printf("Aucune\n");
}

int stat_get_hp(Stat* stat, int* hp) {
	int retour = 0;

	if (stat != NULL)
		*hp = stat->hp;
	else
		retour = 1;

	return retour;
}
int stat_set_hp(Stat* stat, int hp) {
	int retour = 0;

	if (stat != NULL)
		stat->hp = hp;
	else
		retour = 1;

	return retour;
}

int stat_get_attaque(Stat* stat, int* attaque) {
	int retour = 0;

	if (stat != NULL)
		*attaque = stat->attaque;
	else
		retour = 1;

	return retour;
}

int stat_set_attaque(Stat* stat, int attaque) {
	int retour = 0;

	if (stat != NULL)
		stat->attaque = attaque;
	else
		retour = 1;

	return retour;
}


int stat_copie(Stat* dest, Stat src) {
	int retour = 0;

	if (dest != NULL) {
		dest->hp = src.hp;
		dest->attaque = src.attaque;
	}
	else
		retour = 1;

	return retour;
}

int stat_init(Stat* stat, int hp, int attaque) {
	int retour = 0;

	if (stat != NULL) {
		stat->hp = hp;
		stat->attaque = attaque;
	}
	else
		retour = 1;

	return retour;
}

