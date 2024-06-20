//header files
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


void renderText(const std::string& text, TTF_Font* font, SDL_Renderer* renderer, int x, int y) {
    
    //Load all the SDL2 elements.
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x, y, 8, 16};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    //free them
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
}

void textSystem(const std::string& filename, SDL_Renderer* renderer, int delay, int row) {
    std::ifstream file(filename);
    std::string line;

    //current row
    int crow = 0;

    //initialize TTF
    TTF_Init();

    //remember to load your font
    TTF_Font *font = TTF_OpenFont("yourfonthere", 12);

    //same as the CLI version with a few changes
    while(std::getline(file, line)) {
        crow++;
        int posx = 30;
        int posy = 400;
        if( crow == row) {
            for( char c : line ) {

                //c cannot be used inside renderText, so I made this variable.
                std::string text(1, c);

                renderText(text, font, renderer, posx, posy);
                
                //Increase the x position to move each letter
                posx += 10;

                //if the position x of the text is equal to 620, resets them
                if(posx == 620) {
                    posx = 30;
                    posy += 32;

                    //and if the position y of the text is higher than 460
                    //resets the position y and clears the screen before rendering text again
                    if(posy > 460) {
                        posy = 400;
                        SDL_RenderClear(renderer);
                    }
                }

                //ralentize the for loop for every delay (50, 100...) milliseconds time
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            } 

            break;
        }
    }


    TTF_CloseFont(font);
    TTF_Quit();
    
}
