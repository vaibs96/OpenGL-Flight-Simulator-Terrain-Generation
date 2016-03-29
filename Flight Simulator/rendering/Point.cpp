#include "Point.h"
#include <iostream>
using namespace std;


Point::Point()                         // default constructor
{ // default constructor
    x = 0; y = 0; z = 0; w = 1;                 // set to predictable values
} // default constructor

Point::Point(float X, float Y, float Z)// initializing constructor
{ // initializing constructor
    x = X; y = Y; z = Z; w = 1;                 // copy the input values
} // initializing constructor

Point::Point(float X, float Y, float Z, float W)// initializing constructor
{ // initializing constructor
    x = X; y = Y; z = Z; w = W;                 // copy the input values
} // initializing constructor

ostream &operator<< (ostream& ostr, Point p) // C++ print routine
{ // print routine
    ostr << "(" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ")\n";
    return ostr;
} // print routine

Point &Point::operator= (const Point &q)
{ // assignment
    x = q.x;
    y = q.y;
    z = q.z;
    w = q.w;
    return *this;
} //assignment

float &Point::operator[](const int i) // index operator
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

Point Point::operator+ (Vector v) // Point-Vector addtion operator
{ // operator+
    Point q;
    Point p = *this;
    for (int i = 0; i < 4; i++)
        q[i] = p[i] + v[i]; // Assigns the result of addition to each 
                            // coordinate of the point
    return q;
} // operator+

Point Point::operator- (Vector v) // Point-Vector subtraction operator
{ // operator-
    Point q;
    Point p = *this;
    for (int i = 0; i < 4; i++)
        q[i] = p[i] - v[i]; // Assigns the result of subtraction to each 
                            // coordinate of the point
    return q;
} // operator-

Vector Point::operator- (Point head) // Vector from two Points operator
{ // operator -
    Vector v;
    Point tail = *this;
    for (int i = 0; i < 4; i++)
        v[i] = tail[i] - head[i]; // subtract the head Point coordinate from 
                                  // the tail Point coordinate 
    return v;
} // operator -

