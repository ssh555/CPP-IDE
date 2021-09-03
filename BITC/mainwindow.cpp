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
#include <QStringListModel>
#include <QAbstractButton>
#include <QFont>
#include <QGridLayout>
#include "searchwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tBoxFolderMgr = new ToolBox(ui->gBoxFileMgr);
    ui->gBoxFileMgr->setWidget(tBoxFolderMgr);
    openedFileNames = new QStringList;
    TempWidget = NULL;

    //清空编辑页
    for(int i = 0;ui->tabWgtEditArea->count(); ++i)
        ui->tabWgtEditArea->removeTab(i);
    //qDebug() << ui->tabWgtEditArea->currentIndex();
    //编辑页的关闭事件
    connect(ui->tabWgtEditArea,&QTabWidget::tabCloseRequested,[=](int i){
        //文件未保存
        if(ui->tabWgtEditArea->tabText(i).lastIndexOf("(未保存)") != -1){
            QMessageBox messageBox(QMessageBox::Question,"是否保存文件","未保存");
            QPushButton *btnYes = messageBox.addButton(("是"), QMessageBox::YesRole);
            messageBox.addButton(("否"), QMessageBox::NoRole);
            messageBox.exec();
            //保存
            if ((QPushButton*)messageBox.clickedButton() == btnYes){
                emit SIGNAL_SaveFile();
            }
        }
        openedFileNames->removeAll(GetTABFilePath(ui->tabWgtEditArea->widget(i),ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->indexOf(ui->tabWgtEditArea->widget(i)))));
        //如果为临时窗口
        if(TempWidget == ui->tabWgtEditArea->widget(i)){
            TempWidget = NULL;
        }
        ui->tabWgtEditArea->removeTab(i);
    });
    //始终将当前操作文件名指向当前文件
    connect(ui->tabWgtEditArea,&QTabWidget::currentChanged,[=](int i){
        if(i == -1){
            openingFileName.clear();
            return;
        }
        Editor *t = (Editor*)ui->tabWgtEditArea->currentWidget();
        openingFileName = t->FolderName + "/" + ui->tabWgtEditArea->tabText(i).replace("(未保存)","");
    });

    Func_MenuBar();


    /*测试代码*/
    /*测试代码*/

}

MainWindow::~MainWindow()
{
    if (m_pInstance != NULL)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
    delete ui;
    delete openedFileNames;
}

//void MainWindow::resizeEvent(QResizeEvent* event)
//{
//    QMainWindow::resizeEvent(event);
//    // Your code here
//    tBoxFolderMgr->Size_Changed();
//}

//获取C文件绝对路径的文件名.
QString MainWindow::GetCFileName(QString filename){
    return filename.mid(filename.lastIndexOf("/")+1);
}
//获取C文件绝对路径的文件夹名 不包括最后的/
QString MainWindow::GetCFolderName(QString filename){
    return filename.mid(0,filename.lastIndexOf("/"));
}
//获取TAB页对应的文件路径
QString MainWindow::GetTABFilePath(QWidget *TabPage,QString fileName){
    Editor *t = (Editor*) TabPage;
    return  t->FolderName + "/" + fileName;
}

//-----未实现代码，需要在文件夹下展现文件,参数为文件夹完整路径
//参数1 标题    参数2 要显示的QWidget
void MainWindow::AddFolderToGBox(QString foldername){
    //QFileInfo  isfile()  isdir()  判断路径是文件夹还是文件
    FileMgr *fileMgr = new FileMgr(this);
    fileMgr->AddFolderLabel(foldername);
    tBoxFolderMgr->addWidget(QFileInfo(foldername).fileName(), fileMgr);

}

//实现TextEdit类即可  参数为C文件名的完整路径
void MainWindow::AddTextEditToEditArea(QString filename,bool isTemp){
    //打开 临时窗口
    if(isTemp == TabTemp::Temporary){
        if(openedFileNames->contains(filename)){
            ui->tabWgtEditArea->setCurrentIndex(openedFileNames->indexOf(filename));
            return;
        }
        if(TempWidget == NULL){
            TempWidget = CreateEditText(filename);
            Editor *t = (Editor*)TempWidget;
            connect(t,&QPlainTextEdit::textChanged,TempWidget,[=](){
                if(ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->indexOf(TempWidget)).contains("(未保存)")){
                    TempTabToPermTab();
                    //qDebug() << ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->indexOf(TempWidget));
                }
            });
            return;
        }
        //保存当前文件,移出当前文件
        //emit SIGNAL_SaveFile();
        openedFileNames->removeAll(GetTABFilePath(TempWidget,ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->indexOf(TempWidget))));
        //添加选择文件
        openedFileNames->append(filename);
        ui->tabWgtEditArea->setTabText(ui->tabWgtEditArea->indexOf(TempWidget),QFileInfo(filename).fileName());
        //读入文件内容
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QString str = QString(file.readAll());
        file.close();
        //更改标题
        Editor *t = (Editor*)TempWidget;
        isReadingOrWriting = true;
        t->setPlainText(str);
        isReadingOrWriting = false;
        t->isChanged = false;
        ui->tabWgtEditArea->setTabText(ui->tabWgtEditArea->currentIndex(),ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->currentIndex()).replace("(未保存)",""));
        return;
    }


    //打开 非临时窗口
    //若打开的文件为临时窗口文件，则改变临时窗口为非临时窗口
    if(TempWidget != NULL){
        if(openedFileNames->contains(filename)){
            ui->tabWgtEditArea->setCurrentIndex(openedFileNames->indexOf(filename));
            //如果当前文件和临时文件是同一个窗口，则临时文件窗口清空
            if(TempWidget == ui->tabWgtEditArea->currentWidget())
                TempWidget = NULL;
            return;
        }
    }
    //若不是，则新建窗口
    CreateEditText(filename);

    //AddFolderToGBox(GetCFolderName(openingFileName));

}

//-----键盘按下事件,用于快捷键
QAbstractItemModel *MainWindow::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << QString::fromUtf8(line.trimmed());
    }

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    return new QStringListModel(words, completer);
}
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
    //打开文件夹
    if(event->modifiers() == (Qt::ControlModifier | Qt::AltModifier) && event ->key() == Qt::Key_O){
        emit SIGNAL_OpenFolder();
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
    //查找 CTRL + F
    if(event->modifiers() == Qt::ControlModifier && event ->key() == Qt::Key_F){
        emit SIGNAL_Search();
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
    //代码风格
    connect(ui->actioncodeStyle,&QAction::triggered,this,[=](){
        workingEditor->ChangeCodeStyle();
    });
    //查询

    connect(ui->actionFind,&QAction::triggered,this,[=](){
        emit SIGNAL_Search();
        //槽函数得在editor创建后连接,在eidtor那边
    });
    connect(this,&MainWindow::SIGNAL_Search,this,[=](){
        if(workingEditor==NULL){
            return;
        }else
        {
            //新建搜索框,并初始化各槽函数
            searchWindow=new SearchWindow();
            searchWindow->setMinimumSize(682,152);
            searchWindow->move(20,0);
            //设置editor,连接槽函数
            searchWindow->setEditor(workingEditor);
            if(!workingEditor->textCursor().selectedText().isEmpty())
            {
                searchWindow->showWithText(workingEditor->textCursor().selectedText());
            }else searchWindow->show();
        }



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
            AddTextEditToEditArea(filename,TabTemp::Permanent);//非临时窗口
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
        AddTextEditToEditArea(filename,TabTemp::Permanent);//非临时窗口
    });

    //打开文件夹
    connect(ui->actionOpenFolder,&QAction::triggered,this,[=](){
        emit SIGNAL_OpenFolder();
    });
    connect(this,&MainWindow::SIGNAL_OpenFolder,this,[=](){
        QString foldername = QFileDialog::getExistingDirectory(this,"选择需要打开的文件夹",".");
        if(foldername.isEmpty())
            return ;
        AddFolderToGBox(foldername);
    });

    //保存文件
    connect(ui->actionSave,&QAction::triggered,this,[=](){
        emit SIGNAL_SaveFile();
    });
    connect(this,&MainWindow::SIGNAL_SaveFile,this,[=](){
        if(openingFileName.isEmpty()){
            return ;
        }
        //当前页为临时窗口，则变非临时
        if(ui->tabWgtEditArea->currentWidget() == TempWidget)
            TempTabToPermTab();
        Editor *t = (Editor*)ui->tabWgtEditArea->currentWidget();
        QString filename = openingFileName;
        //qDebug() << openingFileName;
        QFile file(filename);
        //        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        //            return ;
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(t->toPlainText().toUtf8().data());
        //qDebug() << t->toPlainText();
        file.close();
        t->isChanged = false;
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
            this->workingEditor=NULL;//把工作中editor置位空,防止ctrl+f出现查询框
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
    if(!QFileInfo(filename.mid(0,filename.lastIndexOf(".")) + ".exe").exists()){
        QMessageBox::critical(this,"编译错误","请检查是否安装了MINGW");
    }
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

//在editarea创建textedit
QWidget* MainWindow::CreateEditText(QString filename){
    if(openedFileNames->contains(filename)){
        ui->tabWgtEditArea->setCurrentIndex(openedFileNames->indexOf(filename));
        return TempWidget;
    }
    //新建页
    openedFileNames->append(filename);

    //设置工作中editor,用于搜索等功能获取
    Editor *editor = new Editor();
//    //创建QGridLayout,用于放置editor及相关组件

//    editorLayout=new QGridLayout(ui->tabWgtEditArea);

//    editorLayout->addWidget(editor,0,0);
//    editorLayout->setRowStretch(0, 8);//设置行列比例系数
//    editorLayout->setRowStretch(1, 1);
//    editorLayout->setSpacing(10);//设置间距

    //设置工作中editor
    workingEditor=editor;

    editor->FolderName = GetCFolderName(filename);
    editor->isChanged = false;


    //设置 代码提示
    completer = new QCompleter(this);
    completer->setModel(modelFromFile(":/resources/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    editor->setCompleter(completer);


    editor->Set_Mode(EDIT);

    //将新建页设为当前显示页
    int i = ui->tabWgtEditArea->addTab(editor,GetCFileName(filename));
    ui->tabWgtEditArea->setCurrentIndex(i);
    //读入文件内容
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QString str = QString(file.readAll());
    file.close();
    //更改标题
    Editor *t = (Editor*)ui->tabWgtEditArea->currentWidget();
    isReadingOrWriting = true;
    t->setPlainText(str);
    isReadingOrWriting = false;
    t->isChanged = false;
    //ui->tabWgtEditArea->setTabText(ui->tabWgtEditArea->currentIndex(),ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->currentIndex()).replace("(未保存)",""));
    //设置 是否保存对应标题的显示
    connect(editor,&QPlainTextEdit::textChanged,[=](){
        if(isReadingOrWriting)
            return ;
        //改变内容但没有保存则标题处标明
        if(!editor->isChanged){
            ui->tabWgtEditArea->setTabText(ui->tabWgtEditArea->currentIndex(),ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->currentIndex()) + "(未保存)");
            editor->isChanged = true;
        }
    });
    return  ui->tabWgtEditArea->currentWidget();
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

//临时TAB页转非临时TAB页
void MainWindow::TempTabToPermTab(){
    if(TempWidget != NULL){
        QString filePath = GetTABFilePath(TempWidget,ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->indexOf(TempWidget)));
        ui->tabWgtEditArea->setCurrentIndex(openedFileNames->indexOf(filePath));
        TempWidget = NULL;
    }
}

MainWindow* MainWindow::m_pInstance = NULL;


