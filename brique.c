#include "brique.h"

int briques[LIGNES][COLONNES] = {{1}};

void dessiner_briques(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int largeur_brique = 60;
    int hauteur_brique = 20;

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            if (briques[i][j] == 1) {
                SDL_Rect brique = {j * (largeur_brique + 10) + 35, i * (hauteur_brique + 10) + 50, largeur_brique, hauteur_brique};
                SDL_RenderFillRect(renderer, &brique);
            }
        }
    }
}
