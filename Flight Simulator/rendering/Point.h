#ifndef POINT_H
#define POINT_H

#include "Vector.h"
#include <iostream>
using namespace std;


class Point 
{ // class Point    
    public:                                 // makes life easier
    float x, y, z, w;                      // the coordinates

    Point();                            // default constructor
    Point(float X, float Y, float Z);   // initializing constructor  
    Point(float X, float Y, float Z, float W);  // 4 value constructor

    Point &operator= (const Point &q);  // assignment operator
    Point operator+ (Vector v); // Point-Vector addition
    Point operator- (Vector v); // Point-Vector subtraction
    Vector operator- (Point head); // Vector from two Points

    float &operator[] (const int i); // index operator 
}; // class Point

ostream &operator<< (ostream & ostr, Point p); // C++ print routine

#endif

