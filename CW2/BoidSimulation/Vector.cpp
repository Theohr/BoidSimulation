#include "Vector.h"

// Vector Class using some mathematical expressions that will be used for the implementation of the simulation 
// Function for the addition in the Vector
Vector Addition(Vector u, Vector v) {
	Vector w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;

	return w;
}

// Function for the difference in the vector
Vector Difference(Vector u, Vector v) {
	Vector w;

	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;

	return w;
}

// Function for the multiplication in the vector
Vector Multiplication(Vector u, float a) {
	Vector w;

	w.x = u.x * a;
	w.y = u.y * a;
	w.z = u.z * a;

	return w;
}

// Dot Product for the vector
float DotProd(Vector u, Vector v) {

	float a = u.x * v.x + u.y * v.y + u.z * v.z;

	return a;
}

// Cross Product for the Vector
Vector CrossProd(Vector u, Vector v) {
	Vector crossProd;

	crossProd.x = u.y * v.z - u.z * v.y;
	crossProd.y = u.z * v.x - u.x * v.z;
	crossProd.z = u.x * v.y - u.y * v.x;

	return crossProd;
}

//Magnitude of the Vector
float Magnitude(Vector u) {
	return sqrt(DotProd(u, u));
}

//Normalization of the Vector
Vector Normalize(Vector u) {
	float norm = Magnitude(u);

	Vector v;

	v.x = u.x / norm;
	v.y = u.y / norm;
	v.z = u.z / norm;

	return v;
}

// Distance in Vector
float Distance(Vector u, Vector v) {

	Vector w = Difference(u, v);

	return Magnitude(w);
}

// Null Vector in class
Vector NullVector() {
	Vector w;

	w.x = 0;
	w.y = 0;
	w.z = 0;

	return w;
}

// New Vector in class
Vector NewVector(float x, float y, float z) {
	Vector w;

	w.x = x;
	w.y = y;
	w.z = z;

	return w;
}