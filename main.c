#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "palette.h"
#include "brique.h"
#include "balle.h"

#define LARGEUR_ECRAN 760
#define HAUTEUR_ECRAN 600

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Casse Briques", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_ECRAN, HAUTEUR_ECRAN, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur d'initialisation de SDL_image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface* image_surface = IMG_Load("fond.png");
    if (!image_surface) {
        printf("Erreur lors du chargement de l'image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);
    if (!image_texture) {
        printf("Erreur lors de la création de la texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation de SDL_ttf: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    TTF_Font* font = TTF_OpenFont("arial_bold.ttf", 24);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police: %s\n", TTF_GetError());
    }

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            briques[i][j] = 1;
        }
    }

    int score = 0;
    Palette* palette = creer_palette((LARGEUR_ECRAN / 2) - 50, HAUTEUR_ECRAN - 50, 100, 20, 5);
    int balle_x = LARGEUR_ECRAN / 2;
    int balle_y = HAUTEUR_ECRAN / 2;
    int taille_balle = 10;
    int vitesse_balle_x = 5;
    int vitesse_balle_y = 5;
    const int vitesse_palette = 10;

    SDL_Event evenement;
    int running = 1;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    while (running) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                running = 0;
            }
        }

        if (keystates[SDL_SCANCODE_LEFT]) {
            deplacer_palette(palette, -vitesse_palette);
        }
        if (keystates[SDL_SCANCODE_RIGHT]) {
            deplacer_palette(palette, vitesse_palette);
        }

        balle_x += vitesse_balle_x;
        balle_y += vitesse_balle_y;

        for (int i = 0; i < LIGNES; i++) {
            for (int j = 0; j < COLONNES; j++) {
                if (briques[i][j] == 1) {
                    int brique_x = j * (60 + 10) + 35;
                    int brique_y = i * (20 + 10) + 50;

                    if (balle_x + taille_balle >= brique_x && balle_x <= brique_x + 60 &&
                        balle_y + taille_balle >= brique_y && balle_y <= brique_y + 20) {
                        briques[i][j] = 0;
                        vitesse_balle_y = -vitesse_balle_y;
                        score += 10;
                    }
                }
            }
        }

        if (balle_x < 0 || balle_x + taille_balle > LARGEUR_ECRAN) {
            vitesse_balle_x = -vitesse_balle_x;
        }
        if (balle_y < 0) {
            vitesse_balle_y = -vitesse_balle_y;
        }
        if (balle_y + taille_balle > HAUTEUR_ECRAN) {
            running = 0;
        }

        Palette* courant = palette;
        while (courant != NULL) {
            if (balle_x + taille_balle >= courant->x && balle_x <= courant->x + courant->l &&
                balle_y + taille_balle >= courant->y && balle_y <= courant->y + courant->h) {
                vitesse_balle_y = -vitesse_balle_y;
                break;
            }
            courant = courant->suivant;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, NULL);
        dessiner_briques(renderer);
        dessiner_balle(renderer, balle_x, balle_y, taille_balle);
        dessiner_palette(renderer, palette);

        SDL_Color color = {255, 255, 255, 255};
        char score_text[50];
        sprintf(score_text, "Score: %d", score);
        SDL_Surface* surface = TTF_RenderText_Solid(font, score_text, color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect_score = {10, 10, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &rect_score);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    liberer_palette(palette);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
