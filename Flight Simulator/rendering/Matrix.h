#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "Vector.h"
#include "Point.h"
using namespace std;

class Matrix  
{ // class Matrix
    public:                              // makes life easier
    float coords[4][4];                  // treat each row as a vector
    
    Matrix();                            // default constructor
    Matrix( float i00, float i01, float i02, float i03, // constructor
            float i10, float i11, float i12, float i13,
            float i20, float i21, float i22, float i23,
            float i30, float i31, float i32, float i33);

    static Matrix Identity();            // returns identity matrix
    static Matrix RotationX(float angle);
    static Matrix RotationY(float angle);
    static Matrix RotationZ(float angle);

    Matrix &operator= (const Matrix &n);  // assignment operator
    Point operator* (Point p); // Matrix-Point product
    Vector operator* (Vector v); // Matrix-Vector product
    Matrix operator+ (Matrix &right); // Matrix addition
    Matrix operator* (Matrix B); // Matrix multiplication

    Vector operator[](int i);            // returns a row as a vector
    Vector column(int j);                // returns a column as vector
}; // class Matrix

ostream &operator<< (ostream & ostr, Matrix m); // C++ print routine

#endif