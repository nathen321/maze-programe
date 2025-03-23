# Raycasting-Based Game
This project is a simple raycasting-based game inspired by classic first-person shooters like Wolfenstein 3D. It uses SDL2 for rendering and input handling, and it implements a basic raycasting algorithm to create a pseudo-3D environment.

# Overview
The game simulates a 3D environment using a 2D grid (worldMap) and raycasting. The player can move around the map, and the walls are rendered in pseudo-3D based on the player's position and orientation.

# Features
Raycasting Algorithm: Renders walls in pseudo-3D using raycasting.

Collision Detection: Prevents the player from walking through walls.

Wall Textures: Different wall types are rendered with unique colors.

Player Movement: The player can move forward, backward, and rotate left/right.

Dynamic Rendering: The game updates in real-time based on player input.

# Requirements
To build and run this project, you need:

SDL2: The Simple DirectMedia Layer library for rendering and input handling.

C Compiler: A C compiler like GCC or Clang.

Make: For building the project (optional).

# Setup
1. Install SDL2
On Linux:
sudo apt-get install libsdl2-dev
On macOS (with Homebrew):
brew install sdl2
On Windows:

Download the SDL2 development libraries from the official website.

Set up the include and library paths in your development environment.

2. Clone the Repository
git clone [https://github.com/your-username/raycasting-game.git](https://github.com/nathen321/maze-programe.git)
cd raycasting-game
3. Build the Project
gcc -o raycasting_game main.c -lSDL2 -lm
4. Run the Game
./raycasting_game

# Code Structure
main.c: The main file containing the game loop, raycasting logic, and rendering code.

worldMap: A 2D array representing the game map. Walls are represented by numbers (1, 2, 3, etc.), and empty spaces are represented by 0.

Player Structure: Stores the player's position (x, y) and orientation (angle).

Raycasting Function: Casts rays from the player's position to determine wall distances and heights.

Collision Detection: Ensures the player cannot move through walls.

# How It Works
Raycasting Algorithm
For each vertical strip of the screen, a ray is cast from the player's position in the direction of the camera plane.

The ray is traced until it hits a wall in the worldMap.

The distance to the wall is calculated, and the height of the wall slice is determined.

The wall slice is drawn on the screen, with the color determined by the wall type.

Collision Detection
The player's new position is checked against the worldMap before updating their position.

If the new position is a wall or out of bounds, the player's movement is blocked.

Rendering
The screen is cleared and redrawn every frame.

Walls are rendered as vertical slices based on the raycasting results.

Horizontal walls are rendered with dimmed colors to differentiate them from vertical walls.

# Controls
W: Move forward.

S: Move backward.

A: Rotate left.

D: Rotate right.

ESC: Quit the game.

# Future Improvements
Textures: Add texture mapping for walls to make the environment more realistic.

Sprites: Add sprites for enemies, objects, and decorations.

Lighting: Implement shading and lighting effects.

Sound: Add background music and sound effects.

Optimization: Improve performance for larger maps and higher resolutions.

# Acknowledgments
Inspired by the raycasting algorithm used in Wolfenstein 3D.

Thanks to the SDL2 community for providing excellent documentation and resources.
