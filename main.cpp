#include "fontchooser.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FontChooser w;

#ifdef Q_OS_LINUX
    w.showFullScreen();
#else
    w.show();
#endif

    return a.exec();
}
