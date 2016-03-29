#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QLayout>
#include "GLPolygonWidget.h"
using namespace std;


int main(int argc, char *argv[])
{ // main()   
    QApplication app(argc, argv); // create the application
    
    /*
        Widgets & Layout
    */

    QWidget *window = new QWidget; // main window widget

    QHBoxLayout *layout = new QHBoxLayout; // layout for main window

    GLPolygonWidget *polygonWidget = new GLPolygonWidget(NULL); // create the GLPolygonWidget
    polygonWidget->readFile( argv[1], atof(argv[2]) ); // read the file from command line arguments

    layout->addWidget(polygonWidget); // add the GLPolygonWidget and tool layout to the main layout
    
    window->setLayout(layout); // show main window with the main layout
    window->show();
    window->resize(1024, 1024); // resize for 512x512 GLPolygonWidget plus sliders

    return app.exec();
} // main()