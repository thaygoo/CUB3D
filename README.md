*This project has been created as part of the 42 curriculum by msochor and huburton*

# cub3d
## Description

cub3d is a simplified 3D rendering engine inspired by Wolfenstein 3D.
The goal of the project is to implement a ray‑casting renderer, handle player movement, collision detection, textured walls, and display a 3D scene using MiniLibX.

The world is defined by a 2D map, and the engine projects it into a pseudo‑3D environment by casting rays from the player’s point of view.

This implementation follows the mandatory requirements of the 42 subject and focuses on correctness, readability, and mathematical clarity.

### Features

* Parsing of .cub configuration file
* Loading of .xpm textures (NO, SO, WE, EA)
* Player spawn and orientation (N, S, E, W)
* Real‑time movement and rotation using keyboard
* Collision detection using a radius around player
* Ray‑casting using the DDA algorithm
* Textured wall projection
* Ceiling and floor rendering    
* 60° FOV

### Map Format

A valid .cub file contains:

    NO ./textures/north.xpm
    SO ./textures/south.xpm
    WE ./textures/west.xpm
    EA ./textures/east.xpm

    F 220,100,0
    C 225,30,0

    111111
    1000N1
    100001
    111111

### Map rules:

* Must be closed by walls
* Only one player start position
* Allowed characters: 0, 1, N, S, E, W


### Technical Overview
#### 1. Player

The player is defined by:
```
Position (x, y) in pixel space
Angle in radians
Movement flags (W/A/S/D, LEFT/RIGHT)
Collision radius
```
Wall collision is checked by sampling the map grid around the player’s radius.

#### 2. Ray‑Casting (DDA)

For each frame, the engine casts 256 (preset window width / 2)rays across a 60° FOV.

Each ray computes:
```
Direction vector
Step direction (±1)
Delta distances
Initial side distances
Grid traversal until a wall is hit
```
When a wall is hit, the perpendicular distance is computed and corrected to avoid fisheye.

#### 3. Projection

Wall height is computed using:
```
line_height = HEIGHT(preset window height) / perpendicular_distance
```
The slice is centered vertically and clamped to screen bounds.

#### 4. Texture Mapping

For each vertical slice:
```
Determine which texture to use (N/S/E/W)
Compute hit position on the wall
Convert to texture coordinate tex_x
Sample texture rows (tex_y) using fixed‑point math
Draw pixel‑accurate textured walls
```
Ceiling and floor are filled with solid RGB colors.

## Instructions

### Controls

```
Key	Action
W	Move forward
S	Move backward
A	Strafe left
D	Strafe right
←	Rotate left
→	Rotate right
```
### Compilation & Execution
#### Build

Run make in the cub3d subdirectory. 
```
make
```
#### Run
Run the executable with map settings file as argument.
```
./cub3d map.cub
```
## Resources

Great tutorial for raycasting:
https://lodev.org/cgtutor/raycasting.html

Nice video explaing raycasting:
https://www.youtube.com/watch?v=g8p7nAbDz6Y

AI was used for better understanding of math formulas used for the raycasting.