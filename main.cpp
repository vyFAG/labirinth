#include "labirinth.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Labirinth w;
    w.show();
    return a.exec();
}
