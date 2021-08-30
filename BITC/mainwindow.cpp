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
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QWidget>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tBoxFolderMgr = new ToolBox(ui->gBoxFileMgr);
    ui->gBoxFileMgr->setWidget(tBoxFolderMgr);

    //清空编辑页
    for(int i = 0;ui->tabWgtEditArea->count(); ++i)
        ui->tabWgtEditArea->removeTab(i);
    //qDebug() << ui->tabWgtEditArea->currentIndex();
    //编辑页的关闭事件
    connect(ui->tabWgtEditArea,&QTabWidget::tabCloseRequested,[=](int i){
        ui->tabWgtEditArea->removeTab(i);   //应该把相应的editor也删了，会内存泄漏
    });
    //始终将当前操作文件名指向当前文件
    connect(ui->tabWgtEditArea,&QTabWidget::currentChanged,[=](int i){
        if(i == -1){
            openingFileName.clear();
            return;
        }
        Editor *t = (Editor*)ui->tabWgtEditArea->currentWidget();
        openingFileName = t->FolderName + "/" + ui->tabWgtEditArea->tabText(i);
    });

    Func_MenuBar();


    /*测试代码*/
    //qDebug() << ui->gBoxFileMgr->width() << "    " << ui->gBoxFileMgr->height();
        tBoxFolderMgr->addWidget(QStringLiteral("Qt"), new FileMgr);
        tBoxFolderMgr->addWidget(QStringLiteral("Qt"), new FileMgr);
    //    AddTextEditToEditArea("File2.txt");
    //CompileC("C:/Users/20994/Desktop/test/test.c++");
    /*测试代码*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::resizeEvent(QResizeEvent* event)
//{
//    QMainWindow::resizeEvent(event);
//    // Your code here
//    tBoxFolderMgr->Size_Changed();
//}

//获取C文件绝对路径的文件名
QString MainWindow::GetCFileName(QString filename){
    return filename.mid(filename.lastIndexOf("/")+1);
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
    Editor *editor = new Editor;
    editor->FolderName = GetCFolderName(filename);
    editor->isChanged = false;
    connect(editor,&QPlainTextEdit::textChanged,[=](){
        //改变内容但没有保存则标题处标明
        if(!editor->isChanged){
            ui->tabWgtEditArea->currentWidget()->setWindowTitle("aaa");
            ui->tabWgtEditArea->setTabText(ui->tabWgtEditArea->currentIndex(),ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->currentIndex()) + "(未保存)");
            editor->isChanged = true;
        }
    });

    //Editor *editor = new Editor();
    editor->Set_Mode(EDIT);
    Highlighter *highlighter = new Highlighter(editor->document());
    highlighter->Start_Highlight();
    int i = ui->tabWgtEditArea->addTab(editor,GetCFileName(filename));
    ui->tabWgtEditArea->setCurrentIndex(i);

}
//-----键盘按下事件,用于快捷键
void MainWindow::keyPressEvent(QKeyEvent  *event){
    //编译并运行 CTRL + ALT +N
    if(event->modifiers() == (Qt::ControlModifier | Qt::AltModifier) && event ->key() == Qt::Key_N){
        emit SIGNAL_CompileRun();
    }
    //新建文件 CTRL + N
    if(event->modifiers() == Qt::ControlModifier && event ->key() == Qt::Key_N){
        emit SIGNAL_CreateNewFile();
    }
    //打开文件 CTRL + O
    if(event->modifiers() == Qt::ControlModifier && event ->key() == Qt::Key_O){
        emit SIGNAL_OpenFile();
    }
    //保存文件 CTRL + S
    if(event->modifiers() == Qt::ControlModifier && event ->key() == Qt::Key_S){
        emit SIGNAL_SaveFile();
    }
    //编译文件 CTRL + B
    if(event->modifiers() == Qt::ControlModifier && event ->key() == Qt::Key_B){
        emit SIGNAL_Compile();
    }
    //运行文件 CTRL + R
    if(event->modifiers() == Qt::ControlModifier && event ->key() == Qt::Key_R){
        emit SIGNAL_Run();
    }
    //编译并运行 CTRL + SHIFT + S
    if(event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event ->key() == Qt::Key_S){
        emit SIGNAL_SaveAsFile();
    }
    //关闭所有文件 CTRL + W
    if(event->modifiers() == Qt::ControlModifier && event ->key() == Qt::Key_W){
        emit SIGNAL_CloseAll();
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
        if(openingFileName.isEmpty())
            return;
        CompileC(openingFileName);
        RunC(openingFileName);
    });

    //新建文件
    connect(ui->actionNewFile,&QAction::triggered,this,[=](){
        emit SIGNAL_CreateNewFile();
    });
    connect(this,&MainWindow::SIGNAL_CreateNewFile,this,[=](){
        QString filename = QFileDialog::getSaveFileName(this,"新建C++文件 记得加入后缀名");
        //取消
        if(filename=="")
            return;
        //无后缀
        if(!filename.isEmpty() && (filename.size() - filename.lastIndexOf(".")) > 5){
            filename += ".c++";
        }
        if(CreateFile(filename))
            AddTextEditToEditArea(filename);
        else
            QMessageBox::warning(this,"警告","文件已存在");
    });

    //打开文件
    connect(ui->actionOpenFile,&QAction::triggered,this,[=](){
        emit SIGNAL_OpenFile();
    });
    connect(this,&MainWindow::SIGNAL_OpenFile,this,[=](){
        QString filename = QFileDialog::getOpenFileName(this,"打开文件",".",tr("C(*.c *.c++ *.cpp)"));
        if(filename.isEmpty())
            return ;
        AddTextEditToEditArea(filename);
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QString str = QString(file.readAll());
        file.close();
        Editor *t = (Editor*)ui->tabWgtEditArea->currentWidget();
        t->setPlainText(str);
        t->isChanged = false;
        ui->tabWgtEditArea->currentWidget()->setWindowTitle("aaa");
        ui->tabWgtEditArea->setTabText(ui->tabWgtEditArea->currentIndex(),ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->currentIndex()).replace("(未保存)",""));
    });

    //保存文件
    connect(ui->actionSave,&QAction::triggered,this,[=](){
        emit SIGNAL_SaveFile();
    });
    connect(this,&MainWindow::SIGNAL_SaveFile,this,[=](){
        if(openingFileName.isEmpty()){
            return ;
        }
        Editor *t = (Editor*)ui->tabWgtEditArea->currentWidget();
        QString filename = openingFileName;
        QFile file(filename);
        //        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        //            return ;
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(t->toPlainText().toUtf8().data());
        //qDebug() << t->toPlainText();
        file.close();
        t->isChanged = false;
        ui->tabWgtEditArea->currentWidget()->setWindowTitle("aaa");
        ui->tabWgtEditArea->setTabText(ui->tabWgtEditArea->currentIndex(),ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->currentIndex()).replace("(未保存)",""));
    });

    //另存文件
    connect(ui->actionSaveAs,&QAction::triggered,this,[=](){
        emit SIGNAL_SaveAsFile();
    });
    connect(this,&MainWindow::SIGNAL_SaveAsFile,this,[=](){
        if(openingFileName.isEmpty())
            return ;
        Editor *t = (Editor*)ui->tabWgtEditArea->currentWidget();
        QString filename = QFileDialog::getSaveFileName(this,"另存文件",".","CppFile(*.cpp);;CFile(*.c)");
        QFile file(filename);
        //        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        //            return ;
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(t->toPlainText().toUtf8().data());
        //qDebug() << t->toPlainText();
        file.close();
    });

    //关闭所有文件
    connect(ui->actionCloseAll, &QAction::triggered, this, [=](){
        emit SIGNAL_CloseAll();
    });
    connect(this, &MainWindow::SIGNAL_CloseAll, this, [=](){
        int count = ui->tabWgtEditArea->count();
        while(count>0){
            emit ui->tabWgtEditArea->tabCloseRequested(0);
            count--;
        }
    });

    //编译文件
    connect(ui->actionCompileRun,&QAction::triggered,this,[=](){
        emit SIGNAL_Compile();
    });
    connect(this,&MainWindow::SIGNAL_Compile,this,[=](){
        if(openingFileName.isEmpty())
            return;
        CompileC(openingFileName);
    });
    //运行文件
    connect(ui->actionRun,&QAction::triggered,this,[=](){
        emit SIGNAL_Run();
    });
    connect(this,&MainWindow::SIGNAL_Run,this,[=](){
        if(openingFileName.isEmpty())
            return;

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
    filename = filename.mid(0,filename.lastIndexOf(".")) + ".exe";
    if(!QFileInfo(filename).exists()){
        QMessageBox::warning(this,"警告","程序未编译");
        return;
    }

    //用系统默认的打开方式打开指定文件
    QDesktopServices::openUrl(QUrl::fromLocalFile(filename));

}
//不存在则创建
bool MainWindow::CreateFile(QString filename){
    QFile file(filename);
    if(file.exists())
        return false;
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    file.close();
    return true;
}


