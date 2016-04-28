#include "gamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qsrand (QDateTime::currentMSecsSinceEpoch());
    QApplication a(argc, argv);
    GameWindow w;
    w.show();

    return a.exec();
}
