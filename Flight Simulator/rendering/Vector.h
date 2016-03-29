#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>
using namespace std;


class Vector 
{ // class Vector
    public:                              // makes life easier
    float x, y, z, w;                       // the coordinates

    Vector();                            // default constructor
    Vector(float X, float Y, float Z);   // initializing constructor
    Vector(float X, float Y, float Z, float W);  // 4 value constructor

    Vector &operator= (const Vector &u);  // assignment operator
    Vector operator- (); // Vector unary minus
    Vector operator+ (Vector u); // Vector addition
    Vector operator- (Vector u); // Vector subtraction
    Vector operator* (float f); // Vector-scalar product

    float dot(Vector u); // dot product
    float magnitude(); // calculates the magnitude of a Vector
    Vector cross(Vector u); // cross product
    Vector normal(); // returns normal of Vector

    float &operator[] (const int i); // index operator     
}; // class Vector

ostream &operator<< (ostream & ostr, Vector v);  // C++ print routine

#endif