#include "GLPolygonWidget.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <QImage>
using namespace std;


GLPolygonWidget::GLPolygonWidget(QWidget *parent): QGLWidget(parent) // constructor
{ // constructor
    setFocusPolicy(Qt::StrongFocus); // key presses detected when window is in focus

    numFaces = 0; // number of faces

    eye = Point(0.0, 256.0, 0.0); // set default eye position
    centre = Point(0.0, 256.0, -1.0); // set default centre position
    up = Vector(0.0, 1.0, 0.0); // set default up vector
    right = Vector(1.0, 0.0, 0.0); // set default right vector
    forward = Vector(0.0, 0.0, -1.0); // set default forward vector
    speed = 1; // set initial speed

    QTimer *timer = new QTimer(this); // create a timer to set refresh rate
    timer->setInterval(floor(1000.0/60.0)); // refresh rate of 60fps
    timer->start(); // start timer

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(movement())); // when timeout occurs update movement
} // constructor

void GLPolygonWidget::initializeGL() // called when OpenGL context is set up
{ // initializeGL()
    glClearColor(0.7, 0.8, 0.85, 0.3); // background colour

    glEnable(GL_LIGHTING); // enables lighting
    glEnable(GL_LIGHT0); // single light source
    glEnable(GL_NORMALIZE); // automatically normalizes normals
    glEnable(GL_DEPTH_TEST); // depth test to render faces in the correct order
    glShadeModel(GL_SMOOTH); // enable smooth shading

    glMatrixMode(GL_PROJECTION); // switch the current matrix to the projection matrix
    glLoadIdentity(); // load the identity matrix
    glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100000.0f); // to put z axis in the correct direction

    GLfloat lightColor[] = {1.0f, 0.99f, 0.9f, 1.0f}; // set light colour

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor); // asign the light color to the light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // assign the light position to the light
    
    glMatrixMode(GL_MODELVIEW); //switch back to the model view matrix

    QImage image; // create a QImage object
    image.load("../textures/terrain_colour.jpg"); // load the earth texture
    QImage glImageEarth = QGLWidget::convertToGLFormat(image); // convert to gl's image format   

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // specify pixel alignment in memory     

    glGenTextures(1, &textureID); // create a texture ID for background     
    glBindTexture(GL_TEXTURE_2D, textureID); // bind as current texture to modify settings

    // set parameters for the earth texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glImageEarth.bits()); 

    // set clamping & interpolation for background texture                                */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
} // initializeGL()
 
void GLPolygonWidget::resizeGL(int w, int h) // called every time the widget is resized
{ // resizeGL()
    glViewport(0, 0, w, h); // set the viewport to the entire widget
} // resizeGL()

void GLPolygonWidget::paintGL() // called every time the widget needs painting
{ // paintGL()    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the widget
             
    glEnable(GL_TEXTURE_2D); // enable texturing

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // set the texture mode for the background
    
    glBindTexture(GL_TEXTURE_2D, textureID); // set the earth texture to texture the sphere

    glEnableClientState(GL_VERTEX_ARRAY); // enable vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY); // enable normal arrays
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); // enable texture coordinate arrays

    glVertexPointer(3, GL_FLOAT, 0, &points[0]); // supply my vertex array
    glNormalPointer(GL_FLOAT, 0, &normals[0]); // supply my normal array
    glTexCoordPointer(2, GL_FLOAT, 0 , &textures[0]); // supply my texture coordinate array

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eye[0], eye[1], eye[2], centre[0], centre[1], centre[2], up[0], up[1], up[2]); // set camera position
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // place light source

    glDrawRangeElements(GL_TRIANGLES, 0, numFaces, numFaces*3, GL_UNSIGNED_INT, &faces[0]); // draw the triangles   

    glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
    glDisableClientState(GL_NORMAL_ARRAY); // disable normal arrays 
    glDisableClientState(GL_TEXTURE_COORD_ARRAY); // disable texture coordinate arrays

    glFlush(); // flush to screen
} // paintGL()

void GLPolygonWidget::keyPressEvent(QKeyEvent *e) // called when a key is pressed
{ // keyPressEvent()
    switch(e->key())
    {
        case Qt::Key_Space :
            speedChange = 1;
            break;
        case Qt::Key_Shift :
            speedChange = -1;
            break;
        case Qt::Key_A :
            rolling = 1;
            break;
        case Qt::Key_D :
            rolling = -1;
            break;
        case Qt::Key_W :
            pitching = -1;
            break;
        case Qt::Key_S :
            pitching = 1;
            break;
        case Qt::Key_Q :
            yawing = 1;
            break;
        case Qt::Key_E :
            yawing = -1;
            break;
    }
} // keyPressEvent()

void GLPolygonWidget::keyReleaseEvent(QKeyEvent *e) // called when a key is released
{ // keyReleaseEvent()
    switch(e->key())
    {
        case Qt::Key_Space :
            speedChange = 0;
            break;
        case Qt::Key_Shift :
            speedChange = 0;
            break;
        case Qt::Key_A :
            rolling = 0;
            break;
        case Qt::Key_D :
            rolling = 0;
            break;
        case Qt::Key_W :
            pitching = 0;
            break;
        case Qt::Key_S :
            pitching = 0;
            break;
        case Qt::Key_Q :
            yawing = 0;
            break;
        case Qt::Key_E :
            yawing = 0;
            break;
    }
} // keyReleaseEvent()

void GLPolygonWidget::pitch(float angle) // used to pitch up or down
{ // pitch()
    forward = (forward * cos(angle)) + (up * sin(angle));
    up = right.cross(forward);

    centre = eye + forward; // update centre position
} // pitch()

void GLPolygonWidget::roll(float angle) // used to roll left or right
{ // roll()
    right = (right * cos(angle)) + (up * sin(angle));
    up = right.cross(forward);

    centre = eye + forward; // update centre position
} // roll()

void GLPolygonWidget::yaw(float angle) // used to yaw left or right
{ // yaw()
    right = (right * cos(angle)) + (forward * sin(angle));
    forward = up.cross(right); 

    centre = eye + forward; // update centre position
} // yaw()

void GLPolygonWidget::speedAdjust(float value) // used to increase or decrease speed
{ // speedAdjust()
    speed = speed + value; // add value to speed
} // speedAdjust()

void GLPolygonWidget::movement()
{ // movement()
    // Checks which keys are pressed and changes orientation and speed as appropriate
    if (speedChange == 0 && yawing == 0 && pitching == 0 && rolling == 0) {
        // Do nothing...
    } else if (speedChange == 0 && yawing == 0 && pitching == 0 && rolling != 0) {
        roll(rolling*rs);
    } else if (speedChange == 0 && yawing == 0 && pitching != 0 && rolling == 0) {
        pitch(pitching*rs);
    } else if (speedChange == 0 && yawing == 0 && pitching != 0 && rolling != 0) {
        roll(rolling*rs); pitch(pitching*rs);
    } else if (speedChange == 0 && yawing != 0 && pitching == 0 && rolling == 0) {
        yaw(yawing*rs);
    } else if (speedChange == 0 && yawing != 0 && pitching == 0 && rolling != 0) {
        roll(rolling*rs); yaw(yawing*rs);
    } else if (speedChange == 0 && yawing != 0 && pitching != 0 && rolling == 0) {
        pitch(pitching*rs); yaw(yawing*rs);
    } else if (speedChange == 0 && yawing != 0 && pitching != 0 && rolling != 0) {
        roll(rolling*rs); pitch(pitching*rs); yaw(yawing*rs);
    } else if (speedChange != 0 && yawing == 0 && pitching == 0 && rolling == 0) {
        speedAdjust(speedChange*as);
    } else if (speedChange != 0 && yawing == 0 && pitching == 0 && rolling != 0) {
        roll(rolling*rs); speedAdjust(speedChange*as);
    } else if (speedChange != 0 && yawing == 0 && pitching != 0 && rolling == 0) {
        pitch(pitching*rs); speedAdjust(speedChange*as);
    } else if (speedChange != 0 && yawing == 0 && pitching != 0 && rolling != 0) {
        roll(rolling*rs); pitch(pitching*rs); speedAdjust(speedChange*as);
    } else if (speedChange != 0 && yawing != 0 && pitching == 0 && rolling == 0) {
        yaw(yawing*rs); speedAdjust(speedChange*as);
    } else if (speedChange != 0 && yawing != 0 && pitching == 0 && rolling != 0) {
        roll(rolling*rs); yaw(yawing*rs); speedAdjust(speedChange*as);
    } else if (speedChange != 0 && yawing != 0 && pitching != 0 && rolling == 0) {
        pitch(pitching*rs); yaw(yawing*rs); speedAdjust(speedChange*as);
    } else if (speedChange != 0 && yawing != 0 && pitching != 0 && rolling != 0) {
        roll(rolling*rs); pitch(pitching*rs); yaw(yawing*rs); speedAdjust(speedChange*as);
    }

    centre = centre + forward*speed*0.1; // update centre position
    eye = eye + forward*speed*0.1; // update eye position

    updateGL();
} // movement()

void GLPolygonWidget::readFile( string fileName, float hs ) // reads in a file and loads into this
{ // readFile
    QImage image; // load image
    image.load(fileName.c_str()); // take filename from argument

    int h, w; // get height and width of image
    h = image.size().height();
    w = image.size().width();

    float** pixels = new float*[h]; // temporary holds the vertices for each face
    for( int i = 0; i < h; i++ )
        pixels[i] = new float[w];

    for( int i = 0; i < w; i++ ) // add all greyvalues of pixel from image to an array
    { // for
        for( int j = 0; j < h; j++ )
        { // for
            pixels[i][j] = qGray(image.pixel(i, j));
        } // for
    } // for

    int min = 255;
    // int max = 0;

    for( int i = 0; i < w; i++ ) // this will find the minimum to ensure that the minimum value is at sea level
    { // for
        for( int j = 0; j < h; j++ )
        { // for
            if( pixels[i][j] < min )
                min = pixels[i][j];
        } // for
    } // for

    for( int i = 0; i < w; i++ ) // this writes the height values to a text file
    { // for
        for( int j = 0; j < h; j++ )
        { // for
            pixels[i][j] += -min;
        } // for
    } // for

    numPoints = w*h; // calculate the number of points
    numFaces = (w-1)*(h-1)*2; // calculate the number of faces

    as = as*hs*h; // apply accelatration scalling based on height scaling and size of the image

    for( int i = 0; i < h; i++ )
    { // for
        for( int j = 0; j < w; j++ )
        { // for
            if( pixels[i][j] == 255 ) // avoids texture mapping issue
                pixels[i][j] = 254;

            // add each point and texture point to the arrays
            points.push_back( { (float(i)-floor(float(w)/2.0f))*float(hs), (pixels[i][j]), (float(j)-floor(float(h)/2.0f))*float(hs) } );
            textures.push_back( { pixels[i][j]/255, 1.0 } );
        } // for
    } // for

    for( int i = 0; i < h-1; i++ )
    { // for
        for( int j = 0; j < w-1; j++ )
        { // for
            // add faces for each quad to arrays
            faces.push_back( ((i*w)+j) );
            faces.push_back( ((i*w)+j)+1 );
            faces.push_back( ((i*w)+j)+w+1 );

            faces.push_back( ((i*w)+j)+w+1 );
            faces.push_back( ((i*w)+j)+w );
            faces.push_back( ((i*w)+j) );
        } // for
    } // for

    findNormals();
} // readFile

void GLPolygonWidget::findNormals()
{ // findNormals
    for( int i = 0; i < numPoints; i++ )
    {
        normals.push_back( { 0.0, 0.0, 0.0 } ); // initialise an array of zero vectors
    }

    for( int i = 0; i < numFaces; i++ )
    {
        Vector v( (points[faces[(i*3)]][0] - points[faces[(i*3)+1]][0]),
                    (points[faces[(i*3)]][1] - points[faces[(i*3)+1]][1]),
                    (points[faces[(i*3)]][2] - points[faces[(i*3)+1]][2]) ); // one vector on triangle
        Vector u( (points[faces[(i*3)]][0] - points[faces[(i*3)+2]][0]),
                    (points[faces[(i*3)]][1] - points[faces[(i*3)+2]][1]),
                    (points[faces[(i*3)]][2] - points[faces[(i*3)+2]][2]) ); // second vector on triangle

        Vector n = v.cross(u); // sum of the normals of all neighbours

        for( int k = 0; k < 3; k++ )
        {
            normals[faces[(i*3)+k]][0] = normals[faces[(i*3)+k]][0] + n[0]; // sum all normals of all faces that the point appears in
            normals[faces[(i*3)+k]][1] = normals[faces[(i*3)+k]][1] + n[1];
            normals[faces[(i*3)+k]][2] = normals[faces[(i*3)+k]][2] + n[2];
        }
    }
} // findNormals