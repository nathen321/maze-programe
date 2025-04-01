//Using SDL and standard IO
#include "demo.h"



int main(int argc, char* argv[])
{
    SDL_Instance* instance = init();
    Player player = { 22.0f, 12.0f, 90.0f, 5.0f, 40.0f };
    int quit = 0;
    SDL_Event e;
    Uint32 previousTime = SDL_GetTicks();


    if (instance == NULL)
    {
        printf("Failed to initialize SDL!\n");
        return 1;
    }

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_W]) {
            movePlayer(&player, deltaTime);
        }
        if (keystates[SDL_SCANCODE_S]) {
            movePlayer(&player, -deltaTime);
        }
        if (keystates[SDL_SCANCODE_A]) {
            player.angle -= player.turnSpeed * deltaTime;
        }
        if (keystates[SDL_SCANCODE_D]) {
            player.angle += player.turnSpeed * deltaTime;
        }

        SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
        SDL_RenderClear(instance->renderer);

        raycast(instance->renderer, &player);

        SDL_RenderPresent(instance->renderer);
    }

    SDL_DestroyRenderer(instance->renderer);
    SDL_DestroyWindow(instance->window);
    SDL_Quit();

    return 0;
}
