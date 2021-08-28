#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <toolbox.h>
#include "FileMgr.h"
#include <QTabWidget>
#include <QKeyEvent>
#include <qprocess.h>
#include <qdesktopservices.h>
#include <QFileInfo>
#include <editor.h>
#include <QDebug>
#include <highlighter.h>
#include <QList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tBoxFolderMgr = new ToolBox(ui->gBoxFileMgr);
    //清空编辑页
    for(int i = 0;ui->tabWgtEditArea->count(); ++i)
        ui->tabWgtEditArea->removeTab(i);
    //qDebug() << ui->tabWgtEditArea->currentIndex();
    //编辑页的关闭事件
    connect(ui->tabWgtEditArea,&QTabWidget::tabCloseRequested,[=](int i){
        ui->tabWgtEditArea->removeTab(i);
    });
    //始终将当前操作文件名指向当前文件
    connect(ui->tabWgtEditArea,&QTabWidget::currentChanged,[=](int i){
        if(i == -1){
            openingFileName.clear();
            return;
        }
        QList<Editor*> tlist=ui->tabWgtEditArea->currentWidget()->findChildren<Editor*>();
        Editor *t = new Editor;
        for(int i=0;i < tlist.size();++i)
        {
            delete t;
            t=tlist.at(i);
        }
        openingFileName = t->FolderName + "/" + ui->tabWgtEditArea->tabText(i);
    });

    Func_MenuBar();


    /*测试代码*/
    //qDebug() << ui->gBoxFileMgr->width() << "    " << ui->gBoxFileMgr->height();
    tBoxFolderMgr->addWidget(QStringLiteral("Qt"), new FileMgr);
    tBoxFolderMgr->addWidget(QStringLiteral("Qt"), new FileMgr);
    AddTextEditToEditArea("File2.txt");
    //CompileC("C:/Users/20994/Desktop/test/test.c++");
    /*测试代码*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    // Your code here
    tBoxFolderMgr->Size_Changed();
}

//获取C文件绝对路径的文件名
QString MainWindow::GetCFileName(QString filename){
    return filename.mid(filename.lastIndexOf("/"));
}
//获取C文件绝对路径的文件夹名 不包括最后的/
QString MainWindow::GetCFolderName(QString filename){
    return filename.mid(0,filename.lastIndexOf("/"));
}
//-----未实现代码，需要在文件夹下展现文件
void MainWindow::AddFolderToGBox(QString foldername){
    //参数1 标题    参数2 要显示的QWidget
    //FileMgr不用管，用来测试的类，也可以封装一下FileMgr，然后用FileMgr
    tBoxFolderMgr->addWidget(QStringLiteral("Qt"), new FileMgr);//用例
}

//实现TextEdit类即可  参数为C文件名的完整路径
void MainWindow::AddTextEditToEditArea(QString filename){
    Editor *editor=new Editor(ui->tabWgtEditArea->currentWidget(),GetCFolderName(filename));


    //Editor *editor = new Editor();
    editor->Set_Mode(EDIT);
    Highlighter *highlighter = new Highlighter(editor->document());
    highlighter->Start_Highlight();
    ui->tabWgtEditArea->addTab(editor,filename);
}
//-----键盘按下事件,用于快捷键
void MainWindow::keyPressEvent(QKeyEvent  *event)
{
    //CTRL + ALT +N
    if(event->modifiers() == (Qt::ControlModifier | Qt::AltModifier) && event ->key() == Qt::Key_N)
    {
        emit SIGNAL_CompileRun();
    }

}
//-----实现菜单栏的功能
void MainWindow::Func_MenuBar(){

    //运行->编译运行
    connect(ui->actionCompileRun,&QAction::triggered,this,[=](){
        emit SIGNAL_CompileRun();
    });
    connect(this,&MainWindow::SIGNAL_CompileRun,this,[=](){
        //qDebug() << "bbb";
//        if(openingFileName.isEmpty())
//            return;
                CompileC(openingFileName);
                RunC(openingFileName);
    });

}
//-----编译C文件  参数为文件的完整绝对路径
void MainWindow::CompileC(QString filename){
    //文件不存在
    if(!QFileInfo(filename).exists()){
        //提示是否保存  如果保存则继续编译
        return;
    }

    //用指针形式
    QProcess *p = new QProcess;
    QString str = "g++ -o " + filename.mid(0,filename.lastIndexOf(".")) + ".exe " + filename;
    //qDebug() << str;
    p->start("cmd.exe", QStringList()<<"/c"<<str);
    p->waitForStarted();
    p->waitForFinished();
}
//运行C文件  参数为文件的完整绝对路径
void MainWindow::RunC(QString filename){
    //文件不存在
    if(!QFileInfo(filename).exists())
        return;
    //用系统默认的打开方式打开指定文件
    QDesktopServices::openUrl(QUrl::fromLocalFile(filename.mid(0,filename.lastIndexOf(".")) + ".exe"));

}



