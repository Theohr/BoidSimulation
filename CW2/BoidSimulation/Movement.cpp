#include "Movement.h"

using namespace std;

// The most complex class is the Movement Class where every movement action the boids take
// is created in here

// We implement the 3 basic rules Boids have to follow (Description in Header Page)

// in Separation Function we get the Boids, create the iteration for the Loop and set a null Vector in Vector Class
// then enter the loop to apply the rule to every Boid in the flock
// getting the magnitude between the difference of the boids and the flocks position 
// if its less than 20 and the id of the check between the boid and the iterator is not equal
// we add the nvelocity vector with the multiplication of the difference bwtween the position of the boid and flocks position 
// and return the velocity vector to the boids

// Same happens with Alignment rule but we multiply with the velocity vector 
// then return the difference between the vcelocity vector and boid's velocity

// Same with the Cohesion Rule 

// Different numbers are used in each rule though to achieve the result and apply them

// Then we have the extra functions where the Boids follow a leader
// in a distance of the difference between the leader and the front Boid of the flock


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


// Function that makes the flock follow a Leader returning the velocity vector of the distance between the leader
Vector towardsLeader(Boids* bj) {

	return Difference((flock->getLeader())->getPosition(), bj->getPosition());

}

// The avoidObstacles function where we get the magnitude of the boids velocity

// Function for the boids to avoid every obstacle in their point of view and not collide with it
void avoidObstacles(Boids* bj) {

	ItObs itr;
	float normS = Magnitude(bj->getVelocity());

	// checks the list of the obstacles
	for (itr = obs.begin(); itr != obs.end(); itr++) {

		// sets the z equal to the z of the boids position
		(*itr).setZ(bj->getPosition().z);

		It itb;
		Vector v, p, r, newV, dir;
		// position between the obstacle and the boids
		Vector towardOb = Difference((*itr).getLocation(), bj->getPosition());

		v = Normalize(bj->getVelocity());
		p = Multiplication(v, DotProd(towardOb, v));
		r = Difference(p, towardOb);

		// gets the dotprod of the distance between them if its greater than 0 
		if (DotProd(towardOb, bj->getVelocity()) > 0) {
			// if the magnitude is less than the radius of the obstacle and the magnitude of the distance between them grater than the radius * 1.5
			if (Magnitude(r) < (*itr).getRadius() && Magnitude(towardOb) < 1.5 * (*itr).getRadius()) {
				// if magnitude not equal 0 
				if (Magnitude(r) != 0) {
					newV = Normalize(Addition(towardOb, Multiplication(Normalize(r), 2 * (*itr).getRadius())));
				}
				// else change direction of the boids
				else {
					dir = CrossProd(Difference(bj->getPosition(), NullVector()), towardOb);
					newV = Normalize(Addition(towardOb, Multiplication(Normalize(dir), 2 * (*itr).getRadius())));
				}
				// and increased speed to avoid the obstacle
				newV = Multiplication(newV, normS);
				bj->setVelocity(newV.x, newV.y, newV.z);
			}
		}
	}
}

// Predator Function to pursue the boids that returns velocity vector towards random boids
Vector pursueBoids(Boids* p) {

	List boids = flock->getBoids();
	Vector v;
	int idx = rand() % (boids.size() + 1) - 1;
	It itb = boids.begin();

	for (int i = 0; i < idx; i++) {
		itb++;
	}

	// get the difference between the position of the predator and position of the boid and follow it
	v = Difference(itb->getPosition(), p->getPosition());
	v = Multiplication(Normalize(v), 5.0);

	return v;
}

// Boids must avoid the predator pursuing them returning the velocity vector for fleeing away
// (p is pointer to predator and b for boids)
Vector fleePredator(Boids* p, Boids* b) {

	float dist = Distance(p->getPosition(), b->getPosition());

	Vector newV = NullVector();
	Vector norm = Normalize(p->getVelocity());
	Vector diff = Difference(b->getPosition(), p->getPosition());
	Vector proj = Multiplication(norm, DotProd(diff, norm));
	Vector r = Difference(proj, diff);

	// if the magnitude between them is less than 15
	if (dist < 20 && Magnitude(r) < 15) {

		newV = Addition(Difference(NullVector(), Normalize(r)), norm);

		// boids must move to flee and not get caught
		if (dist != 0)
		{
			newV = Multiplication(newV, 50 / dist * dist);
		}
		return newV;

	}
	return newV;
}

// Draw a series of cubes as obstacles
void drawObstacles() {

	ItObs itr;

	// for each obstacle in the list draw it
	for (itr = obs.begin(); itr != obs.end(); itr++) {
		(*itr).draw();
	}
}

// Functiuon that draws the boids using OpenGL
// (turn is the direction of the boid,)
void DrawBoids(float x, float y, float z, float turn, int id) {
	float a = 0;

	glColor3f(1, 1, 0);
	glTranslatef(x, y, z);
	glScalef(2, 2, 2);
	glRotatef(turn, 0, 0, 1);

	if (id == LEADER) glColor3f(1.0f, 1.0f, 0.0f);
	else if (id == PREDATOR) glColor3f(1.0f, 0.0f, 0.0f);
	else glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_POLYGON);
	glVertex3f(0.4, 0, a - 0.2);
	glVertex3f(0.6, 0, a - 0.2);
	glVertex3f(0.5, 0.15, 0 - 0.2);
	glEnd();

	glRotatef(-turn, 0, 0, 1);
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-x, -y, -z);
}