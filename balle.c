#include "balle.h"

void dessiner_balle(SDL_Renderer* renderer, int x, int y, int taille_balle) {
    SDL_Rect balle = {x, y, taille_balle, taille_balle};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &balle);
}
