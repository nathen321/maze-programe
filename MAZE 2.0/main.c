//Using SDL and standard IO
#include "demo.h"



int main(int argc, char* argv[])
{
    SDL_Instance* instance = init();
    if (instance == NULL)
    {
        printf("Failed to initialize SDL!\n");
        return 1;
    }
 
    // Initialize the player
    Player player = { 22.0f, 12.0f, 90.0f, 5.0f, 40.0f }; // Start at the center, facing right

    // Main loop flag
    int quit = 0;

    // Event handler
    SDL_Event e;
    Uint32 previousTime = SDL_GetTicks();

    // While application is running
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        // Handle player movement
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_W]) {
            movePlayer(&player, deltaTime); // Move forward
        }
        if (keystates[SDL_SCANCODE_S]) {
            movePlayer(&player, -deltaTime); // Move backward
        }
        if (keystates[SDL_SCANCODE_A]) {
            player.angle -= player.turnSpeed * deltaTime; // Turn left
        }
        if (keystates[SDL_SCANCODE_D]) {
            player.angle += player.turnSpeed * deltaTime; // Turn right
        }

        // Render the game
        SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
        SDL_RenderClear(instance->renderer);

        // Perform raycasting and render walls
        raycast(instance->renderer, &player);

        // Update the screen
        SDL_RenderPresent(instance->renderer);
    }

    // Clean up and quit
    SDL_DestroyRenderer(instance->renderer);
    SDL_DestroyWindow(instance->window);
    SDL_Quit();

    return 0;
}
