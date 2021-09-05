#include "mainwindow.h"

#include "config.h"
#include <QApplication>
#include <QSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName(QString("bit"));
    QCoreApplication::setApplicationName(QString("打架了找组长"));
    Config::GetInstance();//初始化设置
    MainWindow::Instance()->show();
    return a.exec();
}
