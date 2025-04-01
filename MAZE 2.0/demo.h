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
float x, y;
float angle;
float moveSpeed;
float turnSpeed;
} Player;

int checkCollision(Player *player, float newX, float newY);
void movePlayer(Player *player, float deltaTime);



SDL_Instance *init();


int loadMedia(SDL_Instance *instance);


void close(SDL_Instance *instance);

void raycast(SDL_Renderer *renderer, Player *player);

#endif
