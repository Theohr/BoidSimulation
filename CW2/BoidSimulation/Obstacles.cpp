#include "Obstacles.h"

//Constructor 
Obstacles::Obstacles() {
	location = NullVector(); 
	radius = 0; 
	angle = 0;
}

Obstacles::Obstacles(Vector l, float r) {
	location = l; 
	radius = r; 
	angle = 0;
}

// Getters
float Obstacles::getRadius() { 
	return radius; 
}

Vector Obstacles::getLocation() { 
	return location; 
}

// Setter
void Obstacles::setZ(float z) { 
	location.z = z; 
}

// Function that draws the obstacles as cubes using OpenGL
void Obstacles::draw() {

	//draws cubes at loc.x, loc.y and at the height of the radius randomly in the map
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(location.x, location.y, radius);
	glScalef(radius / 2, radius / 2, radius);
	glRotatef(90, 1, 0, 0);
	glRotatef(angle, 0, 1, 0);
	glutSolidCube(1);
	glTranslatef(-location.x, -location.y, -radius);
	glPopMatrix();
}