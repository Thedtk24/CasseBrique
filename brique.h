#ifndef BRIQUE_H
#define BRIQUE_H

#include <SDL2/SDL.h>

#define LIGNES 5
#define COLONNES 10

extern int briques[LIGNES][COLONNES];

void dessiner_briques(SDL_Renderer* renderer);

#endif
