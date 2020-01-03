#include "Movement.h"

using namespace std;

// Seperation Function where bj is a pointer and returning the velocity vector for the Seperation to apply
Vector Separation(Boids* bj) {

	Vector c = NullVector();
	It itb = flock->getIt();
	List boids = flock->getBoids();

	// for each boid 
	for (itb = boids.begin(); itb != boids.end(); itb++) {

		// get the magnitude of the position
		float d = 1 + Magnitude(Difference(bj->getPosition(), (*itb).getPosition()));

		// get the id and apply the rule
		if ((*itb).getID() != bj->getID() && d < 20) {
			c = Addition(c, Multiplication(Difference(bj->getPosition(), (*itb).getPosition()), 1 / (2 * d * d)));
		}	
	}

	// returning the velocity vector
	return c;
}

 // Alignment Function where bj is a pointer and returning the velocity vector for the Alignment to apply
Vector Alignment(Boids* bj) {

	Vector speed = NullVector();
	It itb = flock->getIt();
	List boids = flock->getBoids();

	Boids* tmp;

	// for each boid
	for (itb = boids.begin(); itb != boids.end(); itb++) {

		// get the magnitude of their position
		tmp = &(*itb);
		float d = 1 + Magnitude(Difference(bj->getPosition(), tmp->getPosition()));

		// check the id and apply the rule
		if (bj->getID() != tmp->getID() && d < 20) {
			speed = Addition(speed, Multiplication(tmp->getVelocity(), 1 / (d * d)));
		}
	}

	speed = Multiplication(speed, (float(1) / float(boids.size() - 1)));

	// return the velocity of the vector
	return Difference(speed, bj->getVelocity());
}

// Cohesion Function where bj is a pointer and returning the velocity vector for the Cohesion to apply
Vector Cohesion(Boids* bj) {

	Vector c = NullVector();
	It itb = flock->getIt();
	List boids = flock->getBoids();

	Boids* tmp;

	// for each boid
	for (itb = boids.begin(); itb != boids.end(); itb++) {

		// get the magnitude of each boids position
		tmp = &(*itb);
		float d = 1 + Magnitude(Difference(bj->getPosition(), tmp->getPosition()));

		// chech the id and apply the rule
		if (bj->getID() != tmp->getID() && d < 20) {
			c = Addition(c, Multiplication(tmp->getPosition(), 1 / (2 * d * d)));
		}
	}

	c = Multiplication(c, (float(1) / float(boids.size() - 1)));

	// return the velocity vector 
	return Difference(c, bj->getPosition());
}


// Draw a series of cubes as obstacles
void drawObstacles() {

	ItObs itr;

	// for each obstacle in the list draw it
	for (itr = obs.begin(); itr != obs.end(); itr++) {
		(*itr).draw();
	}
}

// Functiuon that draws the boids 
// (turn is the direction of the boid,)
void DrawBoids(float x, float y, float z, float turn, int id) {

	float dz1 = 0;

	glColor3f(1, 1, 0);
	glTranslatef(x, y, z);
	glScalef(2, 2, 2);
	glRotatef(turn, 0, 0, 1);

	if (id == LEADER) glColor3f(1.0f, 1.0f, 0.0f);
	else if (id == PREDATOR) glColor3f(1.0f, 0.0f, 0.0f);
	else glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_POLYGON);
	glVertex3f(0.4, 0, dz1 - 0.2);
	glVertex3f(0.6, 0, dz1 - 0.2);
	glVertex3f(0.5, 0.15, 0 - 0.2);
	glEnd();

	glRotatef(-turn, 0, 0, 1);
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-x, -y, -z);
}