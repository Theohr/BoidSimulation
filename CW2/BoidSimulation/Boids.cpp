#include "Boids.h"

using namespace std;

// The Constructor indexing each boid 
Boids::Boids(int index) {

	if (index == LEADER) {
		velocity = NewVector(0.1, 0.1, 0.0);
		position = NewVector(-400, -400, 30);
	}
	else if (index == PREDATOR) {
		position = NewVector(rand() % 500 / 1.0 - 250, rand() % 500 / 1.0 - 250, rand() % 500 / 1.0 - 250);
		velocity = NewVector(rand() % 100 / 100.0 - 0.5, rand() % 100 / 100.0 - 0.5, rand() % 100 / 100.0 - 0.5);
	}
	else {
		velocity = NewVector(rand() % 100 / 200.0 - 0.25, rand() % 100 / 200.0 - 0.25, rand() % 100 / 200.0 - 0.25);
		position = NewVector((float)(rand() % 50) / 2 - 450, (float)(rand() % 50) / 2 - 450, 20 + rand() % 7 / 3);
	}

	id = index;
}

// Getters for the position, velocity, id
Vector Boids::getPosition() { 
	return position; 
}

Vector Boids::getVelocity() { 
	return velocity; 
}

int Boids::getID() { 
	return id; 
}

// Setters for the velocity and position of the boids
void Boids::setVelocity(GLdouble x, GLdouble y, GLdouble z) {
	velocity.x = x; 
	velocity.y = y; 
	velocity.z = z;
}

void Boids::setPosition(GLdouble x, GLdouble y, GLdouble z) {
	position.x = x; 
	position.y = y; 
	position.z = z;
}

void Boids::setPosition(Vector p) { 
	position = p; 
}

// Function that uses maths to get the boids velocity then sends everything in the DrawBoids Function in Movement.cpp
void Boids::draw() {
	
	float normal = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	float turn1 = acos(velocity.x / normal) * 180 / PI;
	float turn2 = asin(velocity.y / normal) * 180 / PI;

	if (turn2 < 0) {
		turn1 = -turn1;
	}
		
	turn1 = turn1 - 90;

	glDisable(GL_LIGHTING);
	DrawBoids(position.x, position.y, position.z, turn1, id);
	glEnable(GL_LIGHTING);
}
