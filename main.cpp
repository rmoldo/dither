#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "dither.h"
#include "defs.h"

int main(int argc, char **argv)
{
        if (argc != 2) {
                fprintf(stderr, "ERROR: path to image not secified\n");
                return EXIT_FAILURE;
        }

        if (SDL_Init(SDL_INIT_VIDEO)) {
                fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
                return EXIT_FAILURE;
        }

        IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

        SDL_Window *window = SDL_CreateWindow("Floyd-Steinberg Dithering Algorithm",
                                              100, 100,
                                              SCREEN_WIDTH, SCREEN_HEIGHT,
                                              SDL_WINDOW_SHOWN);

        if (window == NULL) {
                fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
                return EXIT_FAILURE;
        }

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == NULL) {
                SDL_DestroyWindow(window);
                fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
                return EXIT_FAILURE;
        }

        SDL_Rect original_position = {
                .x = 0,
                .y = 0,
                .w = SCREEN_WIDTH / 2,
                .h = SCREEN_HEIGHT
        };

        SDL_Rect modified_position = {
                .x = SCREEN_WIDTH / 2,
                .y = 0,
                .w = SCREEN_WIDTH / 2,
                .h = SCREEN_HEIGHT
        };

        Dither dither {argv[1]};

        dither.dither();
        dither.saveImage("out.jpeg");

        SDL_Surface *original_image = IMG_Load(argv[1]);
        SDL_Texture *original_image_texture = SDL_CreateTextureFromSurface(renderer, original_image);


        SDL_Surface *dither_image = IMG_Load("out.jpeg");
        SDL_Texture *dither_image_texture = SDL_CreateTextureFromSurface(renderer, dither_image);

        int is_running = 1;
        SDL_Event e;
        while (is_running) {
                SDL_WaitEvent(&e);

                switch (e.type) {
                case SDL_KEYDOWN:
                        switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE: case SDLK_q:
                                is_running = 0;
                                break;
                        default:
                                break;
                        }
                }

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, original_image_texture, NULL, &original_position);
                SDL_RenderCopy(renderer, dither_image_texture, NULL, &modified_position);
                SDL_RenderPresent(renderer);
        }

        // Cleanup
        SDL_DestroyTexture(dither_image_texture);
        SDL_FreeSurface(dither_image);

        SDL_DestroyTexture(original_image_texture);
        SDL_FreeSurface(original_image);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        IMG_Quit();
        SDL_Quit();

        return EXIT_SUCCESS;
}
