#include "randimage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RandImage w;
    w.show();
    return a.exec();
}
