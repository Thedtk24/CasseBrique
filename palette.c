#include "palette.h"
#include <stdlib.h>

Palette* creer_palette(int x, int y, int l, int h, int nombre_segments) {
    Palette* tete = NULL;
    Palette* courant = NULL;

    for (int i = 0; i < nombre_segments; i++) {
        Palette* nouveau_segment = (Palette*)malloc(sizeof(Palette));
        nouveau_segment->x = x + i * (l / nombre_segments);
        nouveau_segment->y = y;
        nouveau_segment->l = l / nombre_segments;
        nouveau_segment->h = h;
        nouveau_segment->suivant = NULL;

        if (tete == NULL) {
            tete = nouveau_segment;
        } else {
            courant->suivant = nouveau_segment;
        }
        courant = nouveau_segment;
    }
    return tete;
}

void dessiner_palette(SDL_Renderer* renderer, Palette* palette) {
    Palette* courant = palette;
    while (courant != NULL) {
        SDL_Rect rect = {courant->x, courant->y, courant->l, courant->h};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        courant = courant->suivant;
    }
}

void deplacer_palette(Palette* palette, int dx) {
    Palette* premier_segment = palette;
    Palette* dernier_segment = palette;

    while (dernier_segment->suivant != NULL) {
        dernier_segment = dernier_segment->suivant;
    }

    if (premier_segment->x + dx >= 0 && dernier_segment->x + dernier_segment->l + dx <= 760) {
        Palette* courant = palette;
        while (courant != NULL) {
            courant->x += dx;
            courant = courant->suivant;
        }
    }
}

void liberer_palette(Palette* palette) {
    Palette* courant = palette;
    while (courant != NULL) {
        Palette* suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}
