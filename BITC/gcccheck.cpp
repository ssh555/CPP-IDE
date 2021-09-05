#include "gcccheck.h"
#include<QDebug>
#include<QFileDialog>
gccCheck::gccCheck(QWidget *parent):
    QWidget(parent)
{

}
void gccCheck::gccCheckAndInstall(){
    QProcess cmdprocess(0);
    cmdprocess.start("cmd", QStringList()<<"/c"<<"gcc --version");
    cmdprocess.waitForStarted();
    cmdprocess.waitForFinished();
    cmdoutput=QString::fromLocal8Bit(cmdprocess.readAllStandardOutput());
    //qDebug() << cmdoutput;
    if(cmdoutput.startsWith("gcc")){
        return;
    }
    QString str=QFileDialog::getExistingDirectory(this,"mingw安装地址");
    cmdprocess.start("cmd", QStringList()<<"/c"<<"set path="<<str);
}
