#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <iostream>

#include "Vector.h"

#include <GL/glut.h>

// Obstacle Class storing the location and radius of the obstacle
class Obstacles {

private:

	Vector location;
	float radius;
	float angle;

public:

	// Constructor
	Obstacles();

	//initialize loc and radius
	Obstacles(Vector l, float r);

	//Getters
	float getRadius();
	Vector getLocation();

	//Setter
	void setZ(float z);

	// Function that draws the obstacles
	void draw();
};

#endif 