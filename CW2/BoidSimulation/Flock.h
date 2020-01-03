#ifndef FLOCK_H
#define FLOCK_H

#include <iostream>

#include "Main.h"
#include "Obstacles.h"
#include "Vector.h"
#include "Boids.h"

#define MAX_DIS 120

using namespace std;

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
		int i;
		bool hide;

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

		//// Extra function for user to add boids to the flock but currently not working
		//void addBoid();

		// Extra function to remove boids from the flock
		void removeBoid();

		// Function to update the movements of the flock
		void moveBoids();

		//Function to draw the boids
		void drawBoids();

};

#endif