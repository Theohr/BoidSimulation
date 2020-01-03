#include "Boids.h"

using namespace std;

// The Constructor indexing each boid 
Boids::Boids(int index) {

	if (index == LEADER) {
		velocity = NewVector(0.05, 0.1, 0.0);
		position = NewVector(-400, -400, 10);
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

void Boids::setPosition(Vector pos) { 
	position = pos; 
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

// Invis Walls so boids dont leave the scene with the obstacles
void Boids::walls() {
	if (position.x<-AREA || position.x> AREA) {
		alpha = 180 - alpha;
		position.x = 895 * position.x / AREA;
	}
	if (position.y<-AREA || position.y> AREA) {
		alpha = 360 - alpha;
		position.y = 895 * position.y / AREA;
	}
	if (position.z < 10) {
		beta = 90;
		position.z = 10;
	}
	if (position.z > HEIGHT) {
		beta = 95;
		position.z = HEIGHT;
	}
}

// Move Function which uses the Functions we will implement in Movement.cpp with the basic rules
void Boids::move(Boids* b, int div) {

	Vector temp;
	Vector vec[5];
	float w[5];

	// Check the ID of the boids and sets them their according values for their movement for every action
	if (b->getID() == PREDATOR) {
		w[0] = 0; w[1] = 0; w[2] = 0.002; w[3] = 0; w[4] = 2;
	}
	else if (b->getID() == LEADER) {
		w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; w[4] = .01 / div;
		vec[4] = NullVector();
	}
	else {
		w[0] = 0.01 / div; w[1] = 0.005 / div; w[2] = 0.0005 / div; w[3] = 0.01 / div; w[4] = .01 / div;

	}
	// Gets the Movement rules for the flock set in MOvement
	vec[0] = Multiplication(Separation(b), w[0]);
	vec[1] = Multiplication(Alignment(b), w[1]);
	vec[2] = Multiplication(Cohesion(b), w[2]);

	temp = b->getVelocity();

	// Helps them steer together
	for (int i = 0; i < 5; i++) {
		temp = Addition(temp, vec[i]);
	}

	float norm = Magnitude(temp);

	if (norm > 1)
	{
		temp = Multiplication(temp, 1 / norm);
	}
	if (norm < 0.1) {
		temp = Multiplication(temp, 0.2 / (norm + 0.01));
	}

	b->setVelocity(temp.x, temp.y, temp.z);


	// updating their position 
	position = Addition(position, velocity);

}
