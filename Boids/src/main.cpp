#include "MainWindow.h"
#include <QApplication>
#include <QSurfaceFormat>


// Adapted from:
// https://github.com/NCCA/labcode-jmacey-2/tree/main/ParticleQt

int main(int argc, char *argv[])
{
    // Setup OpenGL format
    QSurfaceFormat format;
    format.setMajorVersion(4);
    format.setMinorVersion(6);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    // Initialize Qt application
    QApplication app(argc, argv);

    // Create and show main window
    MainWindow window;
    window.show();

    // Enter Qt event loop
    return app.exec();
}
