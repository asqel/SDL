#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Créer une fenêtre SDL
    SDL_Window* window = SDL_CreateWindow("SDL2 Square", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur de création de la fenêtre SDL: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Créer un renderer SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur de création du renderer SDL: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Définir les dimensions et la position du carré
    SDL_Rect square;
    square.x = 300;  // Position en x
    square.y = 200;  // Position en y
    square.w = 200;  // Largeur
    square.h = 200;  // Hauteur

    // Boucle principale
    int quit = 0;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Couleur de fond (noir)
        SDL_RenderClear(renderer);

        // Dessiner le carré
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Couleur du carré (rouge)
        SDL_RenderFillRect(renderer, &square);

        // Mettre à jour l'écran
        SDL_RenderPresent(renderer);
    }

    // Nettoyer et quitter
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
