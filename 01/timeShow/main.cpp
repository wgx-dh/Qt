#include "TimeShow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimeShow w;
    w.show();
    return a.exec();
}
