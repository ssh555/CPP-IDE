#include "filelabel.h"

#include <QLabel>
#include <QFileInfo>
#include <QDebug>
#include <mainwindow.h>

FileLabel::FileLabel(QWidget *parent) : QLabel(parent)
{
    Init();
}

FileLabel::FileLabel(QString filename, QWidget *parent) : QLabel(QFileInfo(filename).fileName(),parent)
{
    filePath = filename;
    Init();
}

void FileLabel::SetFilePath(QString path){
    if(filePath.isEmpty()){
        filePath = path;
    }
}

void FileLabel::Init(){
    this->setMargin(2);//设置上下间距
    this->setIndent(16);//设置抬头间距
    //this->setStyleSheet("background:rgba(0,255,255,10)");//设置背景颜色
}

//鼠标移入更改背景颜色
void FileLabel::enterEvent(QEvent *){
    this->setStyleSheet("background:rgba(0,255,255,100)");
}

//鼠标移出更改背景颜色
void  FileLabel::leaveEvent(QEvent *){
    this->setStyleSheet("background:rgba(255,255,255,0)");
}

//鼠标单击打开临时TAB页面
void FileLabel::mousePressEvent(QMouseEvent *){
    MainWindow::Instance()->AddTextEditToEditArea(filePath);
}

//鼠标单击打开页面
void FileLabel::mouseDoubleClickEvent(QMouseEvent *){
    qDebug() << "bbb";
}
