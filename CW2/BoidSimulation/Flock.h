#ifndef FLOCK_H
#define FLOCK_H

#include <iostream>

#include "Main.h"
#include "Obstacles.h"
#include "Vector.h"
#include "Boids.h"

#define MAX_DIS 120

using namespace std;

extern bool hide;
extern int i;

class Boids;
class Obstacles;

typedef std::list<Boids>::iterator It;
typedef std::list<Boids> List;

// FLock Class which stores the list of the flock of our boids
class Flock {

	// Our private functions with the iteration for the loops the least and the size of the flock
	private:
		It it;
		List boids;
		Boids* leader;
		Boids* predator;
		int size;

	public:

		// Constructor
		Flock();

		// Size, Leader, Predator, Iteration and Boids getters
		int getSize();
		Boids* getLeader();
		Boids* getPredator();
		It getIt();
		List getBoids();

		// Calculates the centroid of the flock
		Vector centroid();

		// calculates the radius of the flock
		float radius();

		//Function to draw the boids
		void drawBoids();

};

#endif