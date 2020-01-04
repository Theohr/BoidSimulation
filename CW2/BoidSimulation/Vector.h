#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

// Hello this is a tutorial on how the code is build together for this Boid Simulation to run
// It is built based on 6 classes. The Vector, Boids, Flock, Obstacles, Movement and Main 
// We  start off with the Vector class to define some math expressions that will be used in the rest of the classes 
// And also create a new and a null Vector

// Structure of the Vector class with the floats x,y,z
typedef struct {
	float x;
	float y;
	float z;
} Vector;

// Addition
Vector Addition(Vector u, Vector v);

// Difference
Vector Difference(Vector u, Vector v);

// Multiplication 
Vector Multiplication(Vector u, float a);

//Dot Product Vector
float DotProd(Vector u, Vector v);

//Cross Product Vector
Vector CrossProd(Vector u, Vector v);

//Magnitude Vector
float Magnitude(Vector u);

// Normalization
Vector Normalize(Vector u);

// Distance 
float Distance(Vector u, Vector v);

// Null Vector
Vector NullVector();

// Initialization for each new Vector
Vector NewVector(float x, float y, float z);

#endif