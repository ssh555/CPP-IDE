#include "edittextwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditTextWindow w;
    w.show();
    return a.exec();
}
