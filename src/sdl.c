/**
        \file sdl.c
        \brief Fichier de fonctions pour initialiser la SDL
        \author WIDMER Alexis
        \version 1.0
        \date 13/04/2019

        Ce fichier permet d'initialiser toutes les variables nécessaires pour la SDL, de lancer en plein écran ou fenêtré et également de libérer les variables globales de la SDL.
*/
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#ifdef WINDOWS
#include <winsock2.h>
#endif

#include "../include/affichage_sdl.h"
#include "../include/commun.h"
#include "../include/son.h"

SDL_Window * window;
SDL_Renderer * renderer;

/**
	\fn sdl_init(int fullscreen);
	\brief Initialise la SDL

	\param fullscreen Permet de savoir si l'utilisateur veut avoir le jeu en plein écran ou non
	\return VRAI si la fonction s'est bien déroulée, FAUX s'il y a eu un problème.
*/
int sdl_init(int fullscreen) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		printf("Erreur initialisation SDL: %s\n", SDL_GetError());
		return 0;
	}
	
	if (TTF_Init()) {
		printf("Erreur initialisation SDL_ttf\n");
		return 0;
	}

	if (!init_son()) {
		printf("Erreur initialisation SDL_mixer\n");
		return 0;
	}

	if (fullscreen) {
		window = SDL_CreateWindow("Blokus in C", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, -1, -1, SDL_WINDOW_FULLSCREEN);
	}
	else {
		window = SDL_CreateWindow("Blokus in C", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, L_FENETRE, H_FENETRE, SDL_WINDOW_SHOWN);
	}

	if (!window) {
		printf("%s", SDL_GetError());
		return 0;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		printf("%s", SDL_GetError());
		return 0;
	}


	/* Initialisation du format des images */
	int flags = IMG_INIT_PNG;
	int init_img = IMG_Init(IMG_INIT_PNG);

	if ((init_img&flags) != flags) {
		printf("IMG_Init: Failed to init required png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
	}

	SDL_SetRenderDrawColor(renderer, 54, 57, 63, 255);
	init_affichage_sdl(fullscreen);

	// Initialisation sockets windows
	#ifdef WINDOWS
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	#endif

	return 1;

}

/**
	\fn sdl_close();
	\brief Ferme la SDL et tous les composants ouvert grâce à sdl_init
*/
void sdl_close() {

	IMG_Quit();
	free_son();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	// Fermeture sockets windows
	#ifdef WINDOWS
	WSACleanup();
	#endif

}
