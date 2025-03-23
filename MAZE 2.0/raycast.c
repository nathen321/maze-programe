#include "demo.h"
int worldMap1[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void raycast(SDL_Renderer* renderer, Player* player) {
    // Convert player angle to radians
    float playerAngleRad = player->angle * M_PI / 180.0f;

    // Loop through each vertical strip of the screen
    for (int x = 0; x < screenWidth; x++) {
        // Calculate the ray angle
        float rayAngle = (playerAngleRad - FOV / 2 * M_PI / 180.0f) + (x / (float)screenWidth) * FOV * M_PI / 180.0f;

        // Ray direction
        float rayDirX = cos(rayAngle);
        float rayDirY = sin(rayAngle);

        // Player position on the map
        int mapX = player->x;
        int mapY = player->y;

        // Length of ray from current position to next x or y-side
        float sideDistX;
        float sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        float deltaDistX = fabs(1 / rayDirX);
        float deltaDistY = fabs(1 / rayDirY);
        float perpWallDist;

        // Direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; // Was there a wall hit?
        int side; // Was a NS or a EW wall hit? (0 = vertical, 1 = horizontal)

        // Calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player->x - mapX) * deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (mapX + 1.0f - player->x) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player->y - mapY) * deltaDistY;
        }
        else {
            stepY = 1;
            sideDistY = (mapY + 1.0f - player->y) * deltaDistY;
        }

        // Perform DDA (Digital Differential Analysis)
        while (hit == 0) {
            // Jump to next map square
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // Vertical wall
            }
            else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // Horizontal wall
            }

            // Check if ray has hit a wall
            if (worldMap1[mapX][mapY] > 0) hit = 1;
        }

        // Calculate distance projected on camera direction
        if (side == 0) perpWallDist = (mapX - player->x + (1 - stepX) / 2.0f) / rayDirX;
        else           perpWallDist = (mapY - player->y + (1 - stepY) / 2.0f) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(screenHeight / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Choose wall color
        SDL_Color color;
        switch (worldMap1[mapX][mapY]) {
        case 1:  color = (SDL_Color){ 255, 0, 0, 255 }; break; // Red
        case 2:  color = (SDL_Color){ 0, 255, 0, 255 }; break; // Green
        case 3:  color = (SDL_Color){ 0, 0, 255, 255 }; break; // Blue
        case 4:  color = (SDL_Color){ 255, 255, 0, 255 }; break; // Yellow
        default: color = (SDL_Color){ 255, 255, 255, 255 }; break; // White
        }

        // Dim the color for horizontal walls
        if (side == 1) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        // Draw the vertical stripe
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }
}
