#include "demo.h"


SDL_Instance* init()
{
    // Dynamically allocate memory for the SDL_Instance
    SDL_Instance* instance = (SDL_Instance*)malloc(sizeof(SDL_Instance));
    if (instance == NULL)
    {
        printf("Failed to allocate memory for SDL_Instance!\n");
        return NULL;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        free(instance); // Free allocated memory
        return NULL;
    }

    // Create a window
    instance->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (instance->window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        free(instance); // Free allocated memory
        return NULL;
    }

    // Create a renderer
    instance->renderer = SDL_CreateRenderer(instance->window, -1, SDL_RENDERER_ACCELERATED);
    if (instance->renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(instance->window);
        SDL_Quit();
        free(instance); // Free allocated memory
        return NULL;
    }

    return instance; // Return the initialized instance
}

int loadMedia(SDL_Instance* instance)
{
    // Load splash image
    instance->gXOut = SDL_LoadBMP("x.bmp");
    if (instance->gXOut == NULL)
    {
        printf("Unable to load image x.bmp! SDL_Error: %s\n", SDL_GetError());
        return 0; // Return 0 to indicate failure
    }

    return 1; // Return 1 to indicate success
}

void close(SDL_Instance* instance)
{
    // Free loaded image
    if (instance->gXOut != NULL)
    {
        SDL_FreeSurface(instance->gXOut);
        instance->gXOut = NULL;
    }

    // Destroy window
    if (instance->window != NULL)
    {
        SDL_DestroyWindow(instance->window);
        instance->window = NULL;
    }

    // Quit SDL
    SDL_Quit();

    // Free the SDL_Instance
    free(instance);
}
