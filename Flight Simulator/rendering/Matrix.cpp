#include <iostream>
#include "Matrix.h"
#include <sstream>
#include <iomanip>
using namespace std;


Matrix::Matrix() // default constructor
{ // default constructor
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            coords[i][j] = 0; // set to predictable values
} // default constructor

Matrix::Matrix( float i00, float i01, float i02, float i03, // constructor
                float i10, float i11, float i12, float i13,
                float i20, float i21, float i22, float i23,
                float i30, float i31, float i32, float i33)
{ // constructor
    coords[0][0] = i00; coords[0][1] = i01; // assigns each argument as a value
    coords[0][2] = i02; coords[0][3] = i03; // in the matrix row by row, column
    coords[1][0] = i10; coords[1][1] = i11; // by column
    coords[1][2] = i12; coords[1][3] = i13;
    coords[2][0] = i20; coords[2][1] = i21; 
    coords[2][2] = i22; coords[2][3] = i23;
    coords[3][0] = i30; coords[3][1] = i31; 
    coords[3][2] = i32; coords[3][3] = i33;
} // constructor

Matrix Matrix::Identity() // returns an identity matrix              
{ // identity
    Matrix m;
    for (int i = 0; i < 4; i++)
    { // for
        for (int j = 0; j < 4; j++)
        { // for 
            if (i == j) 
            { // if
                m.coords[i][j] = 1; // assigns all diagonal values 1
            } // if
            else 
            { // if
                m.coords[i][j] = 0; // assigns all other values 0
            } // if
        } // for 
    } // for
    return m;
} // identity

Matrix Matrix::RotationX(float angle)
{
    Matrix m;
    m = m.Identity();
    m.coords[1][1] = cos(angle);
    m.coords[1][2] = -sin(angle);
    m.coords[2][1] = sin(angle);
    m.coords[2][2] = cos(angle);
    return m;
}

Matrix Matrix::RotationY(float angle)
{
    Matrix m;
    m = m.Identity();
    m.coords[0][0] = cos(angle);
    m.coords[0][2] = sin(angle);
    m.coords[2][0] = -sin(angle);
    m.coords[2][2] = cos(angle);
    return m;
}

Matrix Matrix::RotationZ(float angle)
{
    Matrix m;
    m = m.Identity();
    m.coords[0][0] = cos(angle);
    m.coords[0][1] = -sin(angle);
    m.coords[1][0] = sin(angle);
    m.coords[1][1] = cos(angle);
    return m;
}

Matrix &Matrix::operator= (const Matrix &n) // assignment operator
{ // assignment
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            coords[i][j] = n.coords[i][j]; // assigns each value of the matrix
                                           // argument to the new returned
                                           // matrix
    return *this;
} //assignment

Vector Matrix::operator[](int i) // row index operator
{ // operator[]
    return Vector(coords[i][0], coords[i][1], coords[i][2], coords[i][3]);
                                        // returns row i of Matrix as a Point
} // operator[]

Vector Matrix::column(int j) // returns a column as vector
{ // column()
    return Vector(coords[0][j], coords[1][j], coords[2][j], coords[3][j]);
                                    // returns column i of Matric as a Vector
} // column()

ostream &operator<< (ostream & ostr, Matrix m)
{ // print operator
    int l = 0; // variable for the maximum length of digits of each number
    string s; // to hold the string of each number
    stringstream ss(stringstream::in | stringstream::out); 
                                    // used to stream each float as a string
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        { // for
            ss << m.coords[i][j]; // loops through each value of the matrix
            s = ss.str();         // putting each value into s to test

            if (s.length() > l) // if s is has more digits than the previous
                l = s.length(); // largest, then l will be updated
            ss.str(string());   // string and string stream are cleared
            ss.clear();
            s = "";
        } // for

    ostr << "| " << setw(l) << m.coords[0][0] << " | " << setw(l) << m.coords[0][1] << " | " 
    << setw(l) << m.coords[0][2] << " | " << setw(l) << m.coords[0][3] << " |\n"
    << "| " << setw(l) << m.coords[1][0] << " | " << setw(l) << m.coords[1][1] << " | " 
    << setw(l) << m.coords[1][2] << " | " << setw(l) << m.coords[1][3] << " |\n"
    << "| " << setw(l) << m.coords[2][0] << " | " << setw(l) << m.coords[2][1] << " | " 
    << setw(l) << m.coords[2][2] << " | " << setw(l) << m.coords[2][3] << " |\n"
    << "| " << setw(l) << m.coords[3][0] << " | " << setw(l) << m.coords[3][1] << " | " 
    << setw(l) << m.coords[3][2] << " | " << setw(l) << m.coords[3][3] << " |\n" << endl;
    return ostr; // prints out Matrix in a readable format to terminal
} // print operator

Vector Matrix::operator* (Vector v) // Matrix-Vector multiplication operator
{ // operator*
    Matrix m = *this;
    Vector u(0,0,0);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            u[i] += m.coords[i][j] * v[j]; // performs Matrix-Vector 
                                           // multiplication
    return u;
} // operator*

Matrix Matrix::operator+ (Matrix &right) // Matrix addition operator
{ // Matrix addition
    Matrix left = *this;
    Matrix resultMatrix;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            resultMatrix.coords[i][j] = left.coords[i][j] + right.coords[i][j];
                                // each new value of the returned Matrix is the 
                                // sum of the two argument Matrices
    return resultMatrix;
} // Matrix addition

Point Matrix::operator* (Point p) // Matrix-Point product operator
{ // operator*
    Matrix m = *this;
    Point q(0, 0, 0, 0);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            q[i] += m.coords[i][j] * p[j]; // Assigns the result of 
                                           // multiplication to each coordinate
                                           // of the point
    return q;
} // operator*

Matrix Matrix::operator* (Matrix B) // Matrix multiplication operator
{ // operator*
    Matrix A = *this;
    Matrix C;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        { // i,j
            C.coords[i][j] = 0;
            for (int k = 0; k < 4; k++)
                C.coords[i][j] += A.coords[i][k] * B.coords[k][j];
                                            // Performs Matrix multiplication
        } // i,j
    return C;
} // operator*