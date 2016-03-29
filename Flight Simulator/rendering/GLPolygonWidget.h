#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <iostream>
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include <array>
#include <vector>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QTimer>
using namespace std;


class GLPolygonWidget: public QGLWidget
{ // class GLPolygonWidget
    Q_OBJECT

    public:
    GLfloat lightPos[4] = {10000.0f, 20000.0f, 0.0f, 0.05f}; // set light position

    vector<array<float, 3>> points; // vector of arrays to hold vertices
    vector<array<float, 3>> normals; // vector of arrays to hold normals
    vector<int> faces; // vector to hold index of points in each face
    vector<array<float, 2>> textures; // vector of arrays to hold texture coordinates

    // variables to indicate whether or not different types of rotation or accelleration are happening
    int speedChange = 0;
    int yawing = 0;
    int pitching = 0;
    int rolling = 0;

    float rs = 0.01; // rotation speed
    float as = 0.000025; // acceleration speed

    Point eye; // position of eye
    Point centre; // position of centre
    Vector up; // up vector of camera
    Vector right; // right vector of camera
    Vector forward; // forward vector of camera
    float speed; // speed of movement

    int numFaces; // number of faces
    int numPoints; // number of points

    GLuint textureID;
    GLuint textureBytes;

    GLPolygonWidget(QWidget *parent); // constructor
    
    void readFile( string fileName, float hs ); // read in .m file
    
    protected:
    void initializeGL(); // called when OpenGL context is set up
    void resizeGL(int w, int h); // called every time the widget is resized
    void paintGL(); // called every time the widget needs painting
    void findNormals(); // finds normals of all points
    void keyPressEvent(QKeyEvent *e); // when key pressed
    void keyReleaseEvent(QKeyEvent *e); // when key released
    void pitch(float angle); // to pitch aircraft
    void roll(float angle); // to roll aircraft
    void yaw(float angle); // to yaw aircraft
    void speedAdjust(float value); // to change the speed of aircraft

    public slots:
    void movement(); // apply movement changes
}; // class GLPolygonWidget

#endif