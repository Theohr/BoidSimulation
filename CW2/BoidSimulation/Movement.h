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

//After implementing the 3 basic rules for the flock we go on and implement some extra functions to make the simulation more interesting
// 4) Following a Leader
// 5) Avoiding Obstacles
// 6) Predator Pursuing BOids
// 7) Boids Avoiding Predator

// The flock follows a Boid called the Leader
Vector towardsLeader(Boids* bj);

// The flock avoids the random obstacles on their way
void avoidObstacles(Boids* bj);

// Predator pursuing boids
Vector pursueBoids(Boids* b);

// Boids aboiving the predator pursuing them
Vector fleePredator(Boids* p, Boids* b);

// Then we go and draw the boids and obstacles with OpenGL applyuing the movements in the Boid Class]
// Drawing the Cube obstacles
void drawObstacles();

// Drawing the boids
void DrawBoids(float x, float y, float z, float turn, int id);

#endif 