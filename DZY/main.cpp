#include "dzy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGame MG;
    MG.MyGameStart();
    MG.show();

    return a.exec();
}
