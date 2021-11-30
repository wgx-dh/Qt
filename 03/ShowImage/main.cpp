#include "showimage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowImage w;
    w.show();
    return a.exec();
}
