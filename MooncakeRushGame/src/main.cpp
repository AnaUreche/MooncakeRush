#include "MainWindow.h"
#include <QApplication>
#include <QSurfaceFormat>

/// This function was originally written by Jon Macey

int main(int argc, char *argv[])
{

    QSurfaceFormat format;
    format.setSamples(4);
    format.setMajorVersion(4);
    format.setMinorVersion(6);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setBlueBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/// end of function
