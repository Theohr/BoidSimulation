#include "Flock.h"

using namespace std;

// Constructor
Flock::Flock() {
	//creating the leader
	leader = new Boids(LEADER);
	size = 20; // size of the flock

	// loop to create the boids in the flock
	for (i = 1; i < size; i++) {
		Boids* boid = new Boids(i);
		boids.push_back(*boid);
	}

	// creates the predator 
	predator = new Boids(PREDATOR);
}

// Getters
int Flock::getSize() { 
	return size; 
}

It Flock::getIt() { 
	return it; 
}

List Flock::getBoids() { 
	return boids; 
}

Boids* Flock::getLeader() { 
	return leader; 
}

Boids* Flock::getPredator() { 
	return predator; 
}


// Function to draw the boids using the function draw implemented in boids.cpp
void Flock::drawBoids() {
	it = boids.begin();

	// for each boid in the list draw the boid
	for (; it != boids.end(); it++) {
		(*it).draw();
	}
	// draw the predator
	predator->draw();

	// draw the leader
	if (!hide) {
		leader->draw();
	}	
}


// Function that calculates the centroid of the flock returning the vector of the centroid
Vector Flock::centroid() {

	it = boids.begin();
	Vector c = NullVector();

	// for the size of the boid
	for (; it != boids.end(); it++) {

		// gets the position 
		float d = Distance(leader->getPosition(), (*it).getPosition());

		// and sets the max distance the boids have to be to be included in the flock otherwise they run on their own 
		if (d < MAX_DIS) { // not to include boids too far away
			c.x += (*it).getPosition().x;
			c.y += (*it).getPosition().y;
			c.z += (*it).getPosition().z;
		}
	}
	return Multiplication(c, 1.0 / boids.size());
}

// Calculates the radius of the flock  and returns the boid which has the higher distance from the leader
float Flock::radius() {

	it = boids.begin();
	float r = 0.0;

	// checks the flock
	for (; it != boids.end(); it++) {

		// gets the position to find the boid at the far end
		float d = Distance(leader->getPosition(), (*it).getPosition());
		
		if (d > r&& d < MAX_DIS)
		{
			r = d;
		}

	}

	return r;
}