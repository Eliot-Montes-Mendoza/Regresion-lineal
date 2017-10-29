#include "reglin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegLin w;
    w.show();

    return a.exec();
}
