#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Text.cpp"

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("text implementation in SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Set the renderer color to white
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //load the texts and clear the screen after
    textSystem("./texts.csv", renderer, 50, 1);
    SDL_RenderClear(renderer);

    textSystem("./texts.csv", renderer, 50, 3);
    SDL_RenderClear(renderer);


    SDL_Event event;
    bool quit = false;
    while(!quit) {

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                SDL_Quit();
                quit = true;
            }
        }

        SDL_RenderPresent(renderer);
    }

    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}