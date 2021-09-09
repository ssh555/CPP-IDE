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
#include <QFuture>
#include "debuger.h"
#include <QElapsedTimer>
#include "uiinterface.h"
#include "settingwindow.h"
#include "jumpwindow.h"
#include <QDateTime>
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
    connect(ui->tabWgtEditArea,&QTabWidget::tabBarClicked,this,[=](int index){
        if(searchWindow!=NULL)
        {
            searchWindow->setEditor((Editor *)ui->tabWgtEditArea->widget(index));

        }
        workingEditor=(Editor *)ui->tabWgtEditArea->widget(index);
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
        QString tmp = ui->tabWgtEditArea->tabText(i);
        openingFileName = t->FolderName + "/" + tmp.replace("(未保存)","");
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

    delete autoSaveTimer;
    delete ui;
    delete openedFileNames;
}
void MainWindow::OpenHistroyFile(){
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
    //换回之前的主题设置
    isReadingOrWriting = true;
    QFuture<void> ftr = QtConcurrent::run(UIInterface::Instance(),&UIInterface::ChangeCodeStyle);
    ftr.waitForFinished();
    isReadingOrWriting = false;
    //UIInterface::Instance()->ChangeCodeStyle();
    setting->endGroup();
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
    QString a = filename.mid(filename.lastIndexOf("/")+1);
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
    //新建搜索框,并初始化各槽函数
    if(searchWindow==NULL){//创建搜索框
        //workingEditor->isChanged=true;
        searchWindow=new SearchWindow();
        ui->verticalLayout->addWidget(searchWindow);
        //设置editor,连接槽函数
        searchWindow->setEditor(workingEditor);
        if(!workingEditor->textCursor().selectedText().isEmpty())
        {
            searchWindow->showWithText(workingEditor->textCursor().selectedText());

        }else searchWindow->show();
        //workingEditor->isChanged=false;
    }

    if(debuger==nullptr) {
        debuger = new Debuger(nullptr);
        ui->hlayoutDebuger->addWidget(debuger);
        connect(debuger, &Debuger::SIGNAL_DebugerRun, this, [=]{
            if(openingFileName.isEmpty()) {
                //qDebug()<<"Debug: empty file";
                return;
            }
            //qDebug()<<workingEditor->GetBreakPoints();
            debuger->Run(workingEditor, GetCFolderName(openingFileName), GetCFileName(openingFileName));
        });
        debuger->show();
    }
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
    //快速跳转 CTRL + J
    if(event->modifiers() == (Qt::ControlModifier ) && event ->key() == Qt::Key_J){
        emit SIGNAL_Jump();
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
        QFuture<bool> ftr1 = QtConcurrent::run(this,&MainWindow::CompileC,openingFileName);
        ftr1.waitForFinished();
        //编译失败
        if(!ftr1.result())
            return ;
        QFuture<void> ftr2 = QtConcurrent::run(this,&MainWindow::RunC,openingFileName);
        ftr2.waitForFinished();
        //CompileC(openingFileName);
        //RunC(openingFileName);
    });
    //代码风格
    connect(ui->actioncodeStyle,&QAction::triggered,this,[=](){

        SettingWindow *s=new SettingWindow();
        s->show();
    });
    //替换
    connect(ui->actionReplace,&QAction::triggered,this,[=](){
        emit SIGNAL_Replace();
        //槽函数得在editor创建后连接,在eidtor那边
    });
    connect(this,&MainWindow::SIGNAL_Replace,this,[=](){
        ui->tabWgtResArea->setCurrentIndex(0);
        searchWindow->on_btnReplace_clicked();
    });
    //查询

    connect(ui->actionFind,&QAction::triggered,this,[=](){
        emit SIGNAL_Search();
        //槽函数得在editor创建后连接,在eidtor那边
    });
    connect(this,&MainWindow::SIGNAL_Search,this,[=](){
        ui->tabWgtResArea->setCurrentIndex(0);

        searchWindow->on_btnFind_clicked();
        searchWindow->Focus();
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
        emit debuger->SIGNAL_DebugerRun();
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
        QFuture<void> ftr1 = QtConcurrent::run(this,&MainWindow::CompileC,openingFileName);
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
        QFuture<void> ftr2 = QtConcurrent::run(this,&MainWindow::RunC,openingFileName);
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
    //文件不存在
    connect(this,&MainWindow::SIGNAL_NotExist,this,[=](){
        QMessageBox::warning(nullptr,"警告",openingFileName + " 文件不存在");
    });
    //文件不是C/C++
    connect(this,&MainWindow::SIGNAL_NotCorCpp,this,[=]{
        QMessageBox::warning(nullptr,"警告",openingFileName + " 文件不是c,c++,cpp文件");
    });
    //编译错误
    connect(this,&MainWindow::SIGNAL_CompileError,this,[=]{
        QMessageBox::critical(nullptr,"编译错误","请检查是否安装了MINGW");
    });
    //程序未编译
    connect(this,&MainWindow::SIGNAL_NotCompiled,this,[=]{
        QMessageBox::warning(nullptr,"警告","程序未编译");
    });
    //自动保存
    connect(autoSaveTimer,&QTimer::timeout,this,[=](){
        //没有打开任何文件
        if(openedFileNames->count() == 0)
            return ;
        //未开启自动保存
        if(!isAutoSave){
            return ;
        }
        //qDebug() << "aaa";
        emit SIGNAL_AutoSave();
    });
    connect(this,&MainWindow::SIGNAL_AutoSave,this,[=](){
        //未开启自动保存
        if(!isAutoSave){
            return ;
        }
        int len = ui->tabWgtEditArea->count();
        for(int i = 0;i < len; ++i){
            Editor *t = (Editor*)ui->tabWgtEditArea->widget(i);
            if(!ui->tabWgtEditArea->tabText(i).contains("(未保存)"))
                continue;
            QString filename = t->FolderName + "/" + ui->tabWgtEditArea->tabText(i).replace("(未保存)","");
            QString dirName = filename.mid(0,filename.lastIndexOf("."));
            QDir dir(dirName);
            if(!dir.exists()){
                dir.mkdir(dirName);
            }
            QString name = QFileInfo(filename).fileName();
            QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss_");
            filename = dirName + "/" + time + name;
            //filename += QDateTime::currentDateTime().toString("_yyyy-MM-dd_hh:mm");
            //qDebug() << filename;
            QFile file(filename);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            file.write(t->toPlainText().toUtf8().data());
            file.close();
            t->isChanged = false;
            //ui->tabWgtEditArea->setTabText(i,ui->tabWgtEditArea->tabText(i).replace("(未保存)",""));
            ui->tabWgtResArea->setCurrentIndex(2);
            ui->CompileLog->append("  <font style='font-size:16px; background-color:white; color:blue;'>" + time + ":文件 </font><font style='font-size:16px; background-color:white; color:red;'>" + name + "</font> <font style='font-size:16px; background-color:white; color:blue;'>已自动保存至  </font>"
                                                                                                                                  "<font style='font-size:16px; background-color:white; color:red;'>" + filename + "</font>");
        }
    });
    //快速跳转
    connect(ui->actionquickJump_2,&QAction::triggered,this,&MainWindow::SIGNAL_Jump);
    connect(this,&MainWindow::SIGNAL_Jump,this,[=](){
        JumpWindow *j = new JumpWindow();
        j->Init(workingEditor);
        j->show();
    });
    connect(this,&MainWindow::SIGNAL_AddMingw,this,[=](){
        QSettings *setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
        setting->beginGroup("gcccheck");
        QString local=QFileDialog::getExistingDirectory(this,"mingw安装地址");
        //三连
        setting->setValue("mingw",local);
        QProcess p(0);
        //certutil -urlcache -split -f http://files.1f0.de/mingw/mingw-w64-gcc-11.2-stable-r35a-posix-threads.7z 国内镜像，需要用7zip
        //杀毒软件可能会报毒
        p.start("cmd",QStringList()<<"/c"<<"cd /d "<<local<<"&& certutil -urlcache -split -f https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe");
        p.waitForStarted();
        p.waitForFinished();
        QDesktopServices::openUrl(QUrl::fromLocalFile(local+"/mingw-w64-install.exe"));
        //qDebug() << setting->value("mingw").toString();
        setting->endGroup();
        emit SIGNAL_Compile();
    });
}



//-----编译C文件  参数为文件的完整绝对路径
bool MainWindow::CompileC(QString filename){
    //文件不存在
    if(!QFileInfo(filename).exists()){
        emit SIGNAL_NotExist();
        return false;
    }
    //文件不是C/C++
    QString suf = QFileInfo(filename).suffix();
    suf = suf.toLower();
    if(suf.compare("c") != 0 && suf.compare("c++") != 0 && suf.compare("cpp") != 0){
        emit SIGNAL_NotCorCpp();
        return false;
    }
    //文件未保存
    if(ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->currentIndex()).lastIndexOf("(未保存)") != -1){

        QMessageBox messageBox(QMessageBox::Question,"是否编译文件",ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->currentIndex()).replace("(未保存)","") + " 文件未保存,选否则取消编译");
        QPushButton *btnYes = messageBox.addButton(("是"), QMessageBox::YesRole);
        messageBox.addButton(("否"), QMessageBox::NoRole);
        messageBox.exec();
        //保存
        if ((QPushButton*)messageBox.clickedButton() == btnYes){
            emit SIGNAL_SaveFile();
        }
        return false;
    }

    //用指针形式
    QProcess *p = new QProcess;
    //没有配置MINGW
    p->start("cmd.exe",QStringList() << "/c" << "gcc --version");
    p->waitForStarted();
    p->waitForFinished();
    QString cmdoutput = QString::fromLocal8Bit(p->readAllStandardOutput());
    QString str = "";
    if(!cmdoutput.startsWith("gcc")){
        QSettings *setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
        setting->beginGroup("gcccheck");
        QStringList settingList=setting->childKeys();
        if(settingList.isEmpty()){
            emit SIGNAL_AddMingw();
            return false;
        }
        str = str + "set path=" + setting->value(settingList.at(0)).toString() + "/mingw-w64/bin && ";
        //测试代码
        //setting->clear();
        //
        setting->endGroup();

    }
    str = str + " g++ -o " + filename.mid(0,filename.lastIndexOf(".")) + ".exe " + filename;
    //qDebug() << str;
    p->start("cmd.exe", QStringList()<<"/c"<<str);
    QElapsedTimer time;
    time.start();
    p->waitForStarted();
    p->waitForFinished();
    qint64 t = time.elapsed();
    cmdoutput = QString::fromLocal8Bit(p->readAllStandardError());
    str = filename.mid(0,filename.lastIndexOf(".")) + ".exe";
    Instance()->ui->tabWgtResArea->setCurrentIndex(2);//显示编译日志界面
    Instance()->ui->CompileLog->append("————————————————————————————————");
    //编译成功
    if(cmdoutput.compare("") == 0){
        Instance()->ui->CompileLog->append(QString("  %1：Compile %2\n"
                                                   "  - 编译成功\n"
                                                   //"  - 警告：0\n"
                                                   "  - 输出文件名：%3\n"
                                                   "  - 输出大小：%4 KB\n"
                                                   "  - 编译时间：%5 s"
                                                   ).arg(__TIME__).arg(filename).arg(str).arg(QFile(str).size()/1024.0).arg(t/1000.0));
        return true;
    }
    //编译失败
    else{
        Instance()->ui->CompileLog->append(QString("  %1：Compile %2\n"
                                                   "  - 编译失败\n%3").arg(__TIME__).arg(filename).arg(cmdoutput));
        return false;
    }



    //qDebug() << QString::fromLocal8Bit(p->readAllStandardOutput());
    if(!QFileInfo(str).exists()){
        emit SIGNAL_CompileError();
        return false;
    }
    return true;
}

//运行C文件  参数为文件的完整绝对路径
void MainWindow::RunC(QString filename){
    //文件不存在
    filename = filename.mid(0,filename.lastIndexOf(".")) + ".exe";
    if(!QFileInfo(filename).exists()){
        emit SIGNAL_NotCompiled();
        return;
    }

    //用系统默认的打开方式打开指定文件
    system(QString("Run.exe " + filename).toUtf8().data());
    //QDesktopServices::openUrl(QUrl::fromLocalFile(filename));

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
    connect(editor,&Editor::SIGNAL_ChangeFont,UIInterface::Instance(),&UIInterface::SLOT_ChangeCodeFont);
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
        //qDebug() << editor->isChanged;
        if(isReadingOrWriting)
            return ;
        //改变内容但没有保存则标题处标明
        if(!editor->isChanged){
            ui->tabWgtEditArea->setTabText(ui->tabWgtEditArea->indexOf(editor),ui->tabWgtEditArea->tabText(ui->tabWgtEditArea->indexOf(editor)) + "(未保存)");
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

//设置自动保存信号
void MainWindow::SetAutoSave(bool b,int time){
    isAutoSave = b;
    //开启自动保存
    if(isAutoSave){
        //未开始则开始计时
        if(!autoSaveTimer->isActive())
            autoSaveTimer->start(time);//每3分钟自动保存一次
    }
    //关闭自动保存
    else{
        //正在计时
        if(autoSaveTimer->isActive())
            autoSaveTimer->stop();//每停止计时
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
bool MainWindow::isReadingOrWriting = false;


