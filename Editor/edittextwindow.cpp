#include "edittextwindow.h"
#include <stdlib.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <highlighter.h>
#include <QVBoxLayout>
#include <ui_edittextwindow.h>
#include <QGridLayout>
EditTextWindow::EditTextWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //这个Ui并没有什么用
    this->setupUi(this);
    //这个是代码编辑框架主体
    configEditor = new Editor();
    //编辑模式
    configEditor->Set_Mode(EDIT);
    //开始打开C语言文件
    file_path=QFileDialog::getOpenFileName();
    if(file_path.isEmpty())
        return;

    FILE *p =fopen(file_path.toStdString().data(),"r");
    if(p==NULL)
    {
        QMessageBox::information(this,"notify","open file failure.");
        return;
    }

    QString content;
    char buf[1024]={0};

    while(!feof(p)){
        content+=  fgets(buf,sizeof(buf),p);
    }
    fclose(p);
    //c语言文件打开完成,数据都在content里头以QString格式存储
    //把文本放到Editor中
    configEditor->insertPlainText(content);
    //QGridLayout *gridLayout=new QGridLayout(this);
    //显示出来
    configEditor->setParent(this);

    //启动高亮功能
    Highlighter *highlighter = new Highlighter(configEditor->document());
    configEditor->createStandardContextMenu();
}

EditTextWindow::~EditTextWindow()
{
}
