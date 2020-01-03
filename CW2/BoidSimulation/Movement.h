#ifndef MOVEMENT_H
#define MOVEMENT_H		

#include <iostream>
#include <list>

#include "Main.h"
#include "Obstacles.h"
#include "Vector.h"
#include "Boids.h"
#include "Flock.h"

#include <GL/glut.h>

class Boids;
class Obstacles;
class Flock;

extern int size;
extern Flock* flock;

// Movement Class
// This is the most important class in the simulation for the movement of the flock
// Boids function based on 3 basic rules implemented below which are:
// 1) Separation
// 2) Alignment
// 3) Cohesion

// Separation Function Description
// Boids should maintain a certain distance separated from their local flockmates so they avoid bumping into each other and overcrowiding
Vector Separation(Boids* bj);

// Alignment Function Description
// Boids should move the same speed and steer in the same direction as the rest of their flockmates 
Vector Alignment(Boids* bj);

// Cohesion Function Description
// Boids should remain together as a group and move towards the center of mass of the local flock
Vector Cohesion(Boids* bj);

// Then we go and draw the boids and obstacles with OpenGL applyuing the movements in the Boid Class]
// Drawing the Cube obstacles
void drawObstacles();

// Drawing the boids
void DrawBoids(float x, float y, float z, float turn, int id);

#endif 