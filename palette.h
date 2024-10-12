#ifndef PALETTE_H
#define PALETTE_H

#include <SDL2/SDL.h>

typedef struct Palette {
    int x, y;
    int l, h;
    struct Palette* suivant;
} Palette;

Palette* creer_palette(int x, int y, int l, int h, int nombre_segments);
void dessiner_palette(SDL_Renderer* renderer, Palette* palette);
void deplacer_palette(Palette* palette, int dx);
void liberer_palette(Palette* palette);

#endif
