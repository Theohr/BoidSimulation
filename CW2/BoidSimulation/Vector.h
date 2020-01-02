#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

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