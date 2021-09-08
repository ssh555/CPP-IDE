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
    str=QFileDialog::getExistingDirectory(this,"mingw安装地址");
    //确实可以下载但是很慢
    cmdprocess.start("cmd",QStringList()<<"/c"<<"bitsadmin /transfer n "<<
                     "https://sourceforge.net/projects/mingw-w64/files/latest/download#"
                     <<str<<"/mingw.zip");
    cmdprocess.start("cmd",QStringList()<<"/c"<<"expand -F"<<str<<"/mingw.zip "<<str);
    //这句加环境变量只有在当前cmd有用，要反复使用需要在gcc/g++处调用str，即mingw绝对位置（VSCode code runner）
    cmdprocess.start("cmd", QStringList()<<"/c"<<"set path="<<str);
}
