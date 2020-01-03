#ifndef MAIN_H
#define MAIN_H

#include <GL/glut.h>

#include "Vector.h"
#include "Boids.h"
#include "Movement.h"
#include "Obstacles.h"
#include "Flock.h"

#define PI 3.141592653589793238462643
#define ESCAPE_KEY 27
#define AREA 900
#define HEIGHT 100
#define TIMERMSECS 50
#define OBSTACLES 15

class Boids;
class Obstacles;
class Flock;

// creating the public iteration and the list of obstacles
typedef std::list<Obstacles>::iterator ItObs;
extern std::list<Obstacles> obs;

// Function when window resizes for the scene to not mess up
void resize(int width, int height);

// watch over the flock and its movements
void watchFlock();

// init function
void init();

// display function
void display();

// adjust the camera on the flock
void adjustCamera();

// keyboard buttons for user to interact
void userInteractions(unsigned char key, int x, int y);

// Timer function to update the movements
void update(int value);

#endif