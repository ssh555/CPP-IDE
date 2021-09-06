#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
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
#include <QThread>
#include <QtConcurrent>
#include "debuger.h"


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
    //切换编辑页
    connect(ui->tabWgtEditArea,&QTabWidget::tabBarClicked,this,[=](){
        if(searchWindow!=NULL)
        {
            searchWindow->setEditor((Editor *)ui->tabWgtEditArea->currentWidget());
        }
    });
    //编辑页的关闭事件
    connect(ui->tabWgtEditArea,&QTabWidget::tabCloseRequested,[=](int i){
        QString str =ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->indexOf(ui->tabWgtEditArea->widget(i))).replace("(未保存)","");
        //文件未保存
        if(ui->tabWgtEditArea->tabText(i).lastIndexOf("(未保存)") != -1){

            QMessageBox messageBox(QMessageBox::Question,"是否保存文件",str + " 文件未保存");
            QPushButton *btnYes = messageBox.addButton(("是"), QMessageBox::YesRole);
            messageBox.addButton(("否"), QMessageBox::NoRole);
            messageBox.exec();
            //保存
            if ((QPushButton*)messageBox.clickedButton() == btnYes){
                emit SIGNAL_SaveFile();
            }
        }
        //保存打开的文件名


        openedFileNames->removeAll(GetTABFilePath(ui->tabWgtEditArea->widget(i),str));
        //如果为临时窗口
        if(TempWidget == ui->tabWgtEditArea->widget(i)){
            TempWidget = NULL;
        }
        ui->tabWgtEditArea->removeTab(i);
    });
    connect(this,&MainWindow::SIGNAL_SaveOpenedFiles,this,[=](){
        QSettings *setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());

        setting->beginGroup("savedFileName");

        QStringList settingList=setting->childKeys();
        if(!settingList.isEmpty()){//把之前存的东西删掉
            for(int i=0;i<settingList.length();i++){
                setting->remove(settingList.at(i));
            }
        }
        QString *variableStr=new QString();//存那堆现在打开的文件路径
        for(int i=0;i<openedFileNames->length();i++){
            variableStr->setNum(i);
            setting->setValue(*variableStr,openedFileNames->at(i));
        }
        setting->endGroup();
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
    QSettings *setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    setting->beginGroup("savedFileName");
    QStringList settingList=setting->childKeys();
    if(!settingList.isEmpty()){//不为空，就打开之前打开的文件
        for (int i =0; i<settingList.length();i++){
            QString filename = setting->value(settingList.at(i)).toString();

            if(filename.isEmpty())
                return ;
            AddTextEditToEditArea(filename,TabTemp::Permanent);//非临时窗口
        }
    }


    setting->endGroup();
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

//窗口关闭时调用
void MainWindow::closeEvent(QCloseEvent *){
    //如果有未保存文件则询问是否保存
    emit(SIGNAL_SaveOpenedFiles());
    int num = ui->tabWgtEditArea->count();
    for(int i = 0;i < num; ++i){
        emit ui->tabWgtEditArea->tabCloseRequested(0);
    }
}

//获取C文件绝对路径的文件名.
QString MainWindow::GetCFileName(QString filename){
    filename = filename.replace("(未保存)","");
    return filename.mid(filename.lastIndexOf("/")+1);
}
//获取C文件绝对路径的文件夹名 不包括最后的/
QString MainWindow::GetCFolderName(QString filename){
    filename = filename.replace("(未保存)","");
    return filename.mid(0,filename.lastIndexOf("/"));
}
//获取TAB页对应的文件路径
QString MainWindow::GetTABFilePath(QWidget *TabPage,QString fileName){
    fileName = fileName.replace("(未保存)","");
    Editor *t = (Editor*) TabPage;
    return  t->FolderName + "/" + fileName;
}

//-----未实现代码，需要在文件夹下展现文件,参数为文件夹完整路径
//参数1 标题    参数2 要显示的QWidget
void MainWindow::AddFolderToGBox(QString foldername){
    //QFileInfo  isfile()  isdir()  判断路径是文件夹还是文件
    if(FileMgr::openedFolders->contains(foldername))
        return;
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

                }
            });
            return;
        }
        //保存当前文件,移出当前文件
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
    //另存为 CTRL + SHIFT + S
    if(event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event ->key() == Qt::Key_S){
        emit SIGNAL_SaveAsFile();
    }
    //关闭所有文件 CTRL + W
    if(event->modifiers() == Qt::ControlModifier && event ->key() == Qt::Key_W){
        emit SIGNAL_CloseAll();
    }
    //撤销 CTRL + Z
    if(event->modifiers() == Qt::ControlModifier  && event ->key() == Qt::Key_Z){
        emit SIGNAL_Revocate();
    }
    //恢复 CTRL + Y
    if(event->modifiers() == Qt::ControlModifier  && event ->key() == Qt::Key_Y){
        emit SIGNAL_Restore();
    }
    //剪切 CTRL + X
    if(event->modifiers() == Qt::ControlModifier  && event ->key() == Qt::Key_X){
        emit SIGNAL_Shear();
    }
    //复制 CTRL + C
    if(event->modifiers() == Qt::ControlModifier  && event ->key() == Qt::Key_C){
        emit SIGNAL_Copy();
    }
    //粘贴 CTRL + V
    if(event->modifiers() == Qt::ControlModifier  && event ->key() == Qt::Key_V)
        emit SIGNAL_Paste();
    //查找 CTRL + F
    if(event->modifiers() == Qt::ControlModifier && event ->key() == Qt::Key_F){
        emit SIGNAL_Search();
    }
    //替换 CTRL + SHIFT + F
    if(event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event ->key() == Qt::Key_F){
        emit SIGNAL_Replace();
    }



}

//-----实现菜单栏的功能
void MainWindow::Func_MenuBar(){

    //运行->编译运行
    connect(ui->actionCompileRun,&QAction::triggered,this,[=](){
        emit SIGNAL_CompileRun();
    });
    connect(this,&MainWindow::SIGNAL_CompileRun,this,[=](){
        if(openingFileName.isEmpty())
            return;
        QFuture<void> ftr1 = QtConcurrent::run(CompileC,openingFileName);
        ftr1.waitForFinished();
        QFuture<void> ftr2 = QtConcurrent::run(RunC,openingFileName);
        ftr2.waitForFinished();
        //CompileC(openingFileName);
        //RunC(openingFileName);
    });
    //代码风格
    connect(ui->actioncodeStyle,&QAction::triggered,this,[=](){
        workingEditor->isChanged=false;
        QSettings *setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
        int CodeStyleNum=setting->value("codeStyle").toString().toUInt();
        setting->setValue("codeStyle",(CodeStyleNum+1)%3);
        for(int i =0;i<ui->tabWgtEditArea->count();i++){
            Editor *e=(Editor *)ui->tabWgtEditArea->widget(i);
            e->ChangeCodeStyle();
        }

        workingEditor->isChanged=true;

    });
    //替换
    connect(ui->actionReplace,&QAction::triggered,this,[=](){
        emit SIGNAL_Replace();
        //槽函数得在editor创建后连接,在eidtor那边
    });
    connect(this,&MainWindow::SIGNAL_Replace,this,[=](){
        if(workingEditor==NULL){
            return;
        }else
        {
            for(int i =0;i<ui->tabWgtEditArea->count();i++){
                Editor *e=(Editor *)ui->tabWgtEditArea->widget(i);
                e->isChanged=false;
            }

            //新建搜索框,并初始化各槽函数
            if (searchWindow!=NULL){
                //qDebug()<<"notnull";
                ui->verticalLayout->removeWidget(searchWindow);
            }
            searchWindow=new SearchWindow();

            ui->verticalLayout->addWidget(searchWindow);
            //设置editor,连接槽函数
            searchWindow->setEditor(workingEditor);
            if(!workingEditor->textCursor().selectedText().isEmpty())
            {
                searchWindow->showWithText(workingEditor->textCursor().selectedText());
            }else searchWindow->show();
            workingEditor->isChanged=true;
            searchWindow->on_btnReplace_clicked();
            for(int i =0;i<ui->tabWgtEditArea->count();i++){
                Editor *e=(Editor *)ui->tabWgtEditArea->widget(i);
                e->isChanged=true;
            }
        }



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
            workingEditor->isChanged=false;
            //新建搜索框,并初始化各槽函数
            if (searchWindow!=NULL){
                //qDebug()<<"notnull";
                ui->verticalLayout->removeWidget(searchWindow);
            }

            searchWindow=new SearchWindow();
            ui->verticalLayout->addWidget(searchWindow);
            //设置editor,连接槽函数
            searchWindow->setEditor(workingEditor);
            if(!workingEditor->textCursor().selectedText().isEmpty())
            {
                searchWindow->showWithText(workingEditor->textCursor().selectedText());

            }else searchWindow->show();
            workingEditor->isChanged=true;
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
    //调试
    connect(ui->actionDebug,&QAction::triggered,this,[=](){
       emit SIGNAL_Debug();
    });
    connect(this,&MainWindow::SIGNAL_Debug,this,[=](){
        //存储正在准备调试的文件信息
//        qDebug()<<openingFileName;
//        qDebug()<<GetCFileName(openingFileName);
//        qDebug()<<GetCFolderName(openingFileName);
        Debuger *debuger=new Debuger(nullptr, GetCFileName(openingFileName), GetCFolderName(openingFileName), workingEditor->GetBreakPoints());
        //初始化设置
//        debuger->SetFile(GetCFileName(openingFileName));
//        debuger->SetFilePath(GetCFolderName(openingFileName));
//        debuger->SetBreakPoints(workingEditor->GetBreakPoints());
//        debuger->ReadyToStart();
        debuger->show();
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
    connect(ui->actionCompile,&QAction::triggered,this,[=](){
        emit SIGNAL_Compile();
    });
    connect(this,&MainWindow::SIGNAL_Compile,this,[=](){
        if(openingFileName.isEmpty())
            return;
        QFuture<void> ftr1 = QtConcurrent::run(CompileC,openingFileName);
        ftr1.waitForFinished();
        //CompileC(openingFileName);
    });
    //运行文件
    connect(ui->actionRun,&QAction::triggered,this,[=](){
        emit SIGNAL_Run();
    });
    connect(this,&MainWindow::SIGNAL_Run,this,[=](){
        if(openingFileName.isEmpty())
            return;
        QFuture<void> ftr2 = QtConcurrent::run(RunC,openingFileName);
        ftr2.waitForFinished();

        //RunC(openingFileName);
    });

    //撤销
    connect(ui->actionRevocate,&QAction::triggered,this,[=](){
        emit SIGNAL_Revocate();
    });
    connect(this,&MainWindow::SIGNAL_Revocate,this,[=](){
        Editor *t = (Editor *)ui->tabWgtEditArea->currentWidget();
        if(t == NULL)
            return ;
        t->undo();
    });

    //恢复
    connect(ui->actionRestore,&QAction::triggered,this,[=](){
        emit SIGNAL_Restore();
    });
    connect(this,&MainWindow::SIGNAL_Restore,this,[=](){
        Editor *t = (Editor *)ui->tabWgtEditArea->currentWidget();
        if(t == NULL)
            return ;
        t->redo();
    });

    //剪切
    connect(ui->actionShear,&QAction::triggered,this,[=](){
        emit SIGNAL_Shear();
    });
    connect(this,&MainWindow::SIGNAL_Shear,this,[=](){
        Editor *t = (Editor *)ui->tabWgtEditArea->currentWidget();
        if(t == NULL)
            return ;
        t->cut();
    });

    //复制
    connect(ui->actionCopy,&QAction::triggered,this,[=](){
        emit SIGNAL_Copy();
    });
    connect(this,&MainWindow::SIGNAL_Copy,this,[=](){
        Editor *t = (Editor *)ui->tabWgtEditArea->currentWidget();
        if(t == NULL)
            return ;
        t->copy();
    });

    //粘贴
    connect(ui->actionPaste,&QAction::triggered,this,[=](){
        emit SIGNAL_Paste();
    });
    connect(this,&MainWindow::SIGNAL_Paste,this,[=](){
        Editor *t = (Editor *)ui->tabWgtEditArea->currentWidget();
        if(t == NULL)
            return ;
        t->paste();
    });
}

//-----编译C文件  参数为文件的完整绝对路径
void MainWindow::CompileC(QString filename){
    //文件不存在
    if(!QFileInfo(filename).exists()){
        QMessageBox::warning(nullptr,"警告",filename + " 文件不存在");
        return;
    }
    //文件不是C/C++
    QString suf = QFileInfo(filename).suffix();
    suf = suf.toLower();
    if(suf.compare("c") != 0 && suf.compare("c++") != 0 && suf.compare("cpp") != 0){
        QMessageBox::warning(nullptr,"警告",filename + " 文件不是c,c++,cpp文件");
        return;
    }
    //用指针形式
    QProcess *p = new QProcess;
    //没有配置MINGW
    p->start("cmd.exe",QStringList() << "/c" << "gcc --version");
    p->waitForStarted();
    p->waitForFinished();
    QString cmdoutput=QString::fromLocal8Bit(p->readAllStandardOutput());
    if(!cmdoutput.startsWith("gcc")){
        QMessageBox::critical(nullptr,"编译错误","请检查是否安装了MINGW");
        return;
    }
    QString str = "g++ -o " + filename.mid(0,filename.lastIndexOf(".")) + ".exe " + filename;
    //qDebug() << str;
    p->start("cmd.exe", QStringList()<<"/c"<<str);
    p->waitForStarted();
    p->waitForFinished();
    //qDebug() << "——————————————————";
    //qDebug() << QString::fromLocal8Bit(p->readAllStandardOutput());
    if(!QFileInfo(filename.mid(0,filename.lastIndexOf(".")) + ".exe").exists()){
        QMessageBox::critical(nullptr,"编译错误","请检查是否安装了MINGW");
        return;
    }


}

//运行C文件  参数为文件的完整绝对路径
void MainWindow::RunC(QString filename){
    //文件不存在
    filename = filename.mid(0,filename.lastIndexOf(".")) + ".exe";
    if(!QFileInfo(filename).exists()){
        QMessageBox::warning(nullptr,"警告","程序未编译");
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
    //防止searchwindow未替换

    if(searchWindow!=NULL)
    {
        searchWindow->setEditor((Editor *)ui->tabWgtEditArea->currentWidget());
    }
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


///获取UI的控件
//获取tabWgtEditArea
QTabWidget* MainWindow::GettabWgtEditArea(){
    return  ui->tabWgtEditArea;
}
//获取tabWgtResArea
QTabWidget* MainWindow::GettabWgtResArea(){
    return  ui->tabWgtResArea;
}
//获取menubar
QMenuBar* MainWindow::Getmenubar(){
    return  ui->menubar;
}
//获取gBoxFileMgr
QDockWidget* MainWindow::GetgBoxFileMgr(){
    return  ui->gBoxFileMgr;
}
//获取statusbarTips
QStatusBar* MainWindow::GetstatusbarTips(){
    return ui->statusbarTips;
}
//获取toolBar
QToolBar* MainWindow::GettoolBar(){
    return ui->toolBar;
}

MainWindow* MainWindow::m_pInstance = NULL;


