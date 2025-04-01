#ifndef _DEMO_H_
#define _DEMO_H_

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define FOV 66




typedef struct SDL_Instance
{
SDL_Window *window;
SDL_Surface *gScreenSurface;
SDL_Surface *gXOut;
SDL_Renderer *renderer;
} SDL_Instance;

typedef struct
{
    float x, y;       // Player position
    float angle;       // Player orientation in degrees
    float moveSpeed;   // Player movement speed
    float turnSpeed;   // Player turning speed
} Player;

// Function to normalize the orientation to the range [0, 360]
int checkCollision(Player *player, float newX, float newY);
void movePlayer(Player *player, float deltaTime);


//Starts up SDL and creates window
SDL_Instance *init();

//Loads media
int loadMedia(SDL_Instance *instance);

//Frees media and shuts down SDL
void close(SDL_Instance *instance);

void raycast(SDL_Renderer *renderer, Player *player);

#endif
