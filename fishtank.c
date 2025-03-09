#include <SDL2/SDL.h>
#include <stdio.h>

#include "goldfish.c"
#include "plant.c"
#include "coral.c"
#include "dory.c"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Fish Tank",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create goldfish surface
    SDL_Surface* goldfish_surface = SDL_CreateRGBSurfaceFrom(
        (void*)goldfish_data[0],
        GOLDFISH_FRAME_WIDTH,
        GOLDFISH_FRAME_HEIGHT,
        32,
        GOLDFISH_FRAME_WIDTH * 4,
        0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
    );
    if (goldfish_surface == NULL) {
        printf("Goldfish surface could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create goldfish texture
    SDL_Texture* goldfish_texture = SDL_CreateTextureFromSurface(renderer, goldfish_surface);
    SDL_FreeSurface(goldfish_surface);
    if (goldfish_texture == NULL) {
        printf("Goldfish texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create dory surface
    SDL_Surface* dory_surface = SDL_CreateRGBSurfaceFrom(
        (void*)dory_data[0],
        DORY_FRAME_WIDTH,
        DORY_FRAME_HEIGHT,
        32,
        DORY_FRAME_WIDTH * 4,
        0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
    );
    if (dory_surface == NULL) {
        printf("Dory surface could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(goldfish_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create dory texture
    SDL_Texture* dory_texture = SDL_CreateTextureFromSurface(renderer, dory_surface);
    SDL_FreeSurface(dory_surface);
    if (dory_texture == NULL) {
        printf("Dory texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(goldfish_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create plant surface
    SDL_Surface* plant_surface = SDL_CreateRGBSurfaceFrom(
        (void*)plant_data[0],
        PLANT_FRAME_WIDTH,
        PLANT_FRAME_HEIGHT,
        32,
        PLANT_FRAME_WIDTH * 4,
        0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
    );
    if (plant_surface == NULL) {
        printf("Plant surface could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(goldfish_texture);
        SDL_DestroyTexture(dory_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create plant texture
    SDL_Texture* plant_texture = SDL_CreateTextureFromSurface(renderer, plant_surface);
    SDL_FreeSurface(plant_surface);
    if (plant_texture == NULL) {
        printf("Plant texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(goldfish_texture);
        SDL_DestroyTexture(dory_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create coral surface
    SDL_Surface* coral_surface = SDL_CreateRGBSurfaceFrom(
        (void*)coral_data[0],
        CORAL_FRAME_WIDTH,
        CORAL_FRAME_HEIGHT,
        32,
        CORAL_FRAME_WIDTH * 4,
        0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
    );
    if (coral_surface == NULL) {
        printf("Coral surface could not be created. SDL error %s\n", SDL_GetError());
        SDL_DestroyTexture(goldfish_texture);
        SDL_DestroyTexture(dory_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create coral texture
    SDL_Texture* coral_texture = SDL_CreateTextureFromSurface(renderer, coral_surface);
    SDL_FreeSurface(coral_surface);
    if (coral_texture == NULL) {
        printf("Coral texture could not be created SDL error %s\n", SDL_GetError());
        SDL_DestroyTexture(goldfish_texture);
        SDL_DestroyTexture(dory_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Animation variables for goldfish
    int goldfish_x = 200;
    int goldfish_y = 300;
    int goldfish_x_speed = -1;
    int goldfish_y_speed = 1;
    const int goldfish_scale = 10;
    const int goldfish_width = GOLDFISH_FRAME_WIDTH * goldfish_scale;
    const int goldfish_height = GOLDFISH_FRAME_HEIGHT * goldfish_scale;
    const int window_width = 800;
    const int window_height = 600;
    const Uint32 move_interval_x = 100;  // X move interval (10 steps/second)
    const Uint32 move_interval_y = 200;  // Y move interval (5 steps/second)

    // Animation variables for dory
    int dory_x = 100;
    int dory_y = 200;
    int dory_x_speed = 1;
    int dory_y_speed = -1;
    const int dory_scale = 10;
    const int dory_width = DORY_FRAME_WIDTH * dory_scale;
    const int dory_height = DORY_FRAME_HEIGHT * dory_scale;

    // Plant variables
    const int plant_scale = 10;
    const int plant_width = PLANT_FRAME_WIDTH * plant_scale;
    const int plant_height = PLANT_FRAME_HEIGHT * plant_scale;
    const int plant_x = ((WINDOW_WIDTH - plant_width) / 2) + 200;
    const int plant_y = WINDOW_HEIGHT - plant_height;

    // Coral variables
    const int coral_scale = 10;
    const int coral_width = CORAL_FRAME_WIDTH * coral_scale;
    const int coral_height = CORAL_FRAME_HEIGHT * coral_scale;
    const int coral_x = ((WINDOW_WIDTH - coral_width) / 2) - 200;
    const int coral_y = WINDOW_HEIGHT - coral_height;

    // Timing variables for goldfish
    Uint32 goldfish_last_update_x = SDL_GetTicks();
    Uint32 goldfish_last_update_y = SDL_GetTicks();

    // Timing variables for dory
    Uint32 dory_last_update_x = SDL_GetTicks();
    Uint32 dory_last_update_y = SDL_GetTicks();

    // Event loop
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Update goldfish position
        Uint32 current_time = SDL_GetTicks();

        // Goldfish x update
        if (current_time - goldfish_last_update_x >= move_interval_x) {
            goldfish_x += goldfish_x_speed * goldfish_scale;
            if (goldfish_x <= 0) {
                goldfish_x = 0;
                goldfish_x_speed = 1;
            } else if (goldfish_x >= WINDOW_WIDTH - goldfish_width) {
                goldfish_x = WINDOW_WIDTH - goldfish_width;
                goldfish_x_speed = -1;
            }
            goldfish_last_update_x = current_time;
        }

        // Goldfish y update
        if (current_time - goldfish_last_update_y >= move_interval_y) {
            goldfish_y += goldfish_y_speed * goldfish_scale;
            if (goldfish_y <= 0) {
                goldfish_y = 0;
                goldfish_y_speed = 1;
            } else if (goldfish_y >= WINDOW_HEIGHT - goldfish_height) {
                goldfish_y = WINDOW_HEIGHT - goldfish_height;
                goldfish_y_speed = -1;
            }
            goldfish_last_update_y = current_time;
        }

        // Update dory position
        // Dory x update
        if (current_time - dory_last_update_x >= move_interval_x) {
            dory_x += dory_x_speed * dory_scale;
            if (dory_x <= 0) {
                dory_x = 0;
                dory_x_speed = 1;
            } else if (dory_x >= WINDOW_WIDTH - dory_width) {
                dory_x = WINDOW_WIDTH - dory_width;
                dory_x_speed = -1;
            }
            dory_last_update_x = current_time;
        }

        // Dory y update
        if (current_time - dory_last_update_y >= move_interval_y) {
            dory_y += dory_y_speed * dory_scale;
            if (dory_y <= 0) {
                dory_y = 0;
                dory_y_speed = 1;
            } else if (dory_y >= WINDOW_HEIGHT - dory_height) {
                dory_y = WINDOW_HEIGHT - dory_height;
                dory_y_speed = -1;
            }
            dory_last_update_y = current_time;
        }

        // Clear screen to blue
        SDL_SetRenderDrawColor(renderer, 30, 123, 255, 255);
        SDL_RenderClear(renderer);

        // Render the coral
        SDL_Rect coral_dest = {coral_x, coral_y, coral_width, coral_height};
        SDL_RenderCopy(renderer, coral_texture, NULL, &coral_dest);

        // Render the goldfish
        SDL_Rect goldfish_dest = {goldfish_x, goldfish_y, goldfish_width, goldfish_height};
        SDL_RendererFlip goldfish_flip = (goldfish_x_speed > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer, goldfish_texture, NULL, &goldfish_dest, 0.0, NULL, goldfish_flip);

        // Render the dory
        SDL_Rect dory_dest = {dory_x, dory_y, dory_width, dory_height};
        SDL_RendererFlip dory_flip = (dory_x_speed > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer, dory_texture, NULL, &dory_dest, 0.0, NULL, dory_flip);

        // Render the plant
        SDL_Rect plant_dest = {plant_x, plant_y, plant_width, plant_height};
        SDL_RenderCopy(renderer, plant_texture, NULL, &plant_dest);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(goldfish_texture);
    SDL_DestroyTexture(dory_texture);
    SDL_DestroyTexture(plant_texture);
    SDL_DestroyTexture(coral_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}