#include "mainwindow.h"

#include "config.h"
#include <QApplication>
#include <QSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow::Instance()->show();
    return a.exec();
}
