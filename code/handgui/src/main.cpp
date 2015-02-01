#include <QtGui/QApplication>
#include "CMakeQt.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CMakeQt w;
    w.show();
    return app.exec();
}
