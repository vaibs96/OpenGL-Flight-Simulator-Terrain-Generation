#include "Vector.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;


Vector::Vector()                         // default constructor
{ // default constructor
    x = 0; y = 0; z = 0; w = 0;                 // set to predictable values
} // default constructor

Vector::Vector(float X, float Y, float Z)// initializing constructor
{ // initializing constructor
    x = X; y = Y; z = Z; w = 0;                 // copy the input values
} // initializing constructor

Vector::Vector(float X, float Y, float Z, float W)// initializing constructor
{ // initializing constructor
    x = X; y = Y; z = Z; w = W;                 // copy the input values
} // initializing constructor

ostream &operator<< (ostream& ostr, Vector v) // C++ print routine
{ // print routine
    int l = 0; // variable for the maximum length of digits of each number
    string s; // to hold the string of each number
    stringstream ss(stringstream::in | stringstream::out); 
                                    // used to stream each float as a string
    for (int i = 0; i < 4; i++)
    { // for
        ss << v[i]; // loops through each value of the vector
        s = ss.str();         // putting each value into s to test

        if (s.length() > l) // if s is has more digits than the previous
            l = s.length(); // largest, then l will be updated
        ss.str(string());   // string and string stream are cleared
        ss.clear();
        s = "";
    } // for

    ostr << "| " << setw(l) << v.x << " |\n| " << setw(l) << v.y << " |\n| "
                 << setw(l) << v.z << " |\n| " << setw(l) << v.w << " |\n";
    return ostr;
} // print routine

Vector &Vector::operator= (const Vector &u)
{ // assignment
    x = u.x;
    y = u.y;
    z = u.z;
    w = u.w;
    return *this;
} //assignment

float &Vector::operator[](const int i) // index operator
{ // operator[]
    switch(i)                       // depending on the index
    { // switch on index i
        case 0: return x;          // x is equivalent to index 0
        case 1: return y;          // y is equivalent to index 1
        case 2: return z;          // z is equivalent to index 2
        case 3: return w;
        default:
            cout << "Error:...";
            return x;                // we have to return something
    } // switch on i
} // operator[]

Vector Vector::operator- () // unary minus operator
{ // operator-
    Vector u;
    Vector v = *this;
    for (int i = 0; i < 4; i++)
        u[i] = v[i] * -1; // negates each value of the Vector
    return u;
} // operator-

Vector Vector::operator+ (Vector u) // Vector addition operator
{ // operator+
    Vector t;
    Vector v = *this;
    for (int i = 0; i < 4; i++)
        t[i] = v[i] + u[i]; // sums each value of the Vector for the new value
    return t;
} // operator+

Vector Vector::operator- (Vector u) // Vector subtraction operator
{ // operator-
    Vector t;
    Vector v = *this;
    for (int i = 0; i < 4; i++)
        t[i] = v[i] - u[i]; // subtracts the value of the second Vector from
                            // the first Vector for the new Vector produced
    return t;
} // operator-

Vector Vector::operator* (float f) // Vector-scalar multiplication operator
{ // operator*
    Vector u;
    Vector v = *this;
    for (int i = 0; i < 4; i++)
        u[i] = v[i] * f; // multiplies each value of the vector by the scalar
    return u;
} // operator*

float Vector::dot(Vector u) // calculates the dot product of two Vectors
{ // dot product
    float f = 0;
    Vector v = *this;
    for (int i = 0; i < 4; i++)
        f += v[i] * u[i]; // calculates the dot product of two Vectors as the
                          // sum of the product of each value i in the Vectors
    return f;
} // dot product

Vector Vector::cross(Vector u) // calculates the cross product of two Vectors
{ // cross product
    Vector t;
    Vector v = *this;
    t[0] = (v[1] * u[2]) - (v[2] * u[1]); // Calculates the cross product of
    t[1] = (v[2] * u[0]) - (v[0] * u[2]); // two Vectors
    t[2] = (v[0] * u[1]) - (v[1] * u[0]);
    return t;
} // cross product

float Vector::magnitude() // calculates the magnitude of a Vector
{ // magnitude
    float f = 0;
    Vector v = *this;
    for (int i = 0; i < 4; i++)
        f += v[i]*v[i]; // Calculates the magnitude of a Vector by the square
                        // root of the sum of each value of the Vector squared
    return sqrt(f);
} // magnitude

Vector Vector::normal() // returns a normal of the Vector
{ // normal
    Vector v = *this;
    float m;
    m = v.y/v.x; // calculates m based on change in y / change in x

    Vector n(-m, 1, 0); // normal Vector created

    return n;
} // normal