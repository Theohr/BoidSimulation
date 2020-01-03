#ifndef BOIDS_H
#define BOIDS_H

#include <GL/glut.h>

#include <iostream>

#include "Vector.h"
#include "Movement.h"
#include "Main.h"

// Indicatind the Leader and the Predator
#define LEADER 0
#define PREDATOR 99

// The Boid Class storing each indivisual boid in the flock
class Boids {

	private:
		Vector position;
		Vector velocity;
		int id;
		float alpha;
		float beta;

	public:
		// The boid constructor
		Boids(int index);

		// Getters for the position velocity and id
		Vector getPosition();
		Vector getVelocity();
		int getID();

		// Setters
		void setPosition(GLdouble x, GLdouble y, GLdouble z);
		void setPosition(Vector pos);
		void setVelocity(GLdouble x, GLdouble y, GLdouble z);

		// Function to draw the boids
		void draw();

		// Function to update boid movement
		void move(Boids* b, int div);

		// Putting some invis walls in the scene so boids dont run wild outside of it
		void walls();
};

#endif