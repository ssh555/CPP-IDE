#include "debuger.h"
#include "ui_debuger.h"
#include <QDebug>
#include "mainwindow.h"

//2021/9/4:
//总体思路就是用cmd启动gdb调试：
//    输入：按钮映射到指令，在cmd中输入指令
//    输出：获取gdb的调试数据，处理后在相应控件中显示。
//问题：
//    输出的数据不好处理，目前想出两种办法，但都没有根本解决问题：
//        1：将gdb的log输出重定向到某个文件，程序再从文件中读取数据
//        2：直接从控制台中读取数据，之后做进一步处理
//    至于能不能控制gdb以方便读取的格式输出，我暂时没找到。
//修改文件名，改26行的a.c
//先设置break point， 然后start，然后设置display

//2021/9/5：
//构造函数参数传入：
//	filename：文件名
//	filepath：文件夹名，不包含文件
//	breakPoint：断点数组，int型，具体看参数列表
//传出：
//	当前行号，以信号方式
//有问题找我（史星蔚）

QRegExp Debuger::lineNumber = QRegExp("^#.* at .*:.*");
QRegExp Debuger::variable = QRegExp("[0-9]{1,4}: .* = .*");

Debuger::Debuger(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Debuger)
{
    ui->setupUi(this);

    //风格
    QSettings *setting =new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    QString qssfilename="";
    switch(setting->value("styleflag").toUInt()){
    case 1: qssfilename=":/qss/bitDebuger.qss";break;
    case 2: qssfilename=":/qss/purpleDebuger.qss";break;
    case 3: qssfilename=":/qss/defaultDebuger.qss";break;
    default: break;
    }
    QFile file(qssfilename);
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = tr(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }

    connect(ui->Start, &QPushButton::clicked, this, [=]{
       emit SIGNAL_DebugerRun();
    });

    connect(ui->Stop, &QPushButton::clicked, this, [=]{
        Write("q");
        Write("y");
    });

    connect(ui->StepInto, &QPushButton::clicked, this, [=]{
        LogWrite("step");
    });

    connect(ui->StepOut, &QPushButton::clicked, this, [=]{
        LogWrite("finish");
    });

    connect(ui->StepOver, &QPushButton::clicked, this, [=]{
        LogWrite("next");
    });

    connect(ui->Continue, &QPushButton::clicked, this, [=]{
        LogWrite("continue");
    });

    connect(ui->DisplayButton, &QPushButton::clicked, this, [=]{
        Write("display "+ui->DisplayLine->text());
        ui->DisplayLine->clear();
    });

    debuger = new QProcess();
    debuger->start("cmd.exe");
    connect(debuger, &QProcess::readyRead, this, &Debuger::Read);
}

Debuger::~Debuger()
{
    delete ui;
    debuger->close();
    delete debuger;
    QFile::remove(filePath+"/main.exe");
}

void Debuger::Write(QString command)
{
//    qDebug()<<command;
    command+="\r\n";
    debuger->write(command.toLatin1().data(), command.length());
}

void Debuger::LogWrite(QString command)
{
    Write(command);
    Write("frame");
}

void Debuger::Read()
{
    QString log  = QString::fromLocal8Bit(debuger->readAll());
//    ui->Information->append(log);
//    ui->Information->update();
    log.replace("(gdb) ","");
    QStringList tempList = log.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    foreach(QString string, tempList) {
//            qDebug()<<string;
        int temp = -1;

        //判断是否含有行号字符串
        temp = lineNumber.indexIn(string);
        if(temp>=0) {
            int number = string.mid(string.lastIndexOf(':')+1).replace("\r\n", "").toInt();
//            ui->NowLineNumber->setText(QString::number(number));
            //qDebug()<<number;
            emit SIGNAL_NowLine(number);
        }

        //判断是否含有变量字符串
        temp = variable.indexIn(string);
        if(temp>=0) {
//            qDebug()<<string<<"  "<<temp;
            QString before = string.mid(temp);
//            ui->DisplayView->append(string.mid(temp));
            int id = before.left(before.indexOf(": ")).toInt();
            QString name = before.mid(before.indexOf(": ")+2).left(before.indexOf(" = ")-3);
            QString value = before.mid(before.indexOf(" = ")+3);
//            qDebug()<<id<<"  "<<name<<"  "<<value;
            if(ui->DisplayView->rowCount()<id) {
                ui->DisplayView->setRowCount(id);
                //qDebug()<<ui->DisplayView->rowCount();
            }
            ui->DisplayView->setItem(id-1, 0, new QTableWidgetItem(name));
            ui->DisplayView->setItem(id-1, 1, new QTableWidgetItem(value));
        }
    }
}

void Debuger::Run(Editor *workingeditor, QString filepath, QString filename) {
    if(workingEditor!=nullptr) {
        disconnect(connectionLineNumber);
    }
    workingEditor = workingeditor;
    connectionLineNumber = connect(this, &Debuger::SIGNAL_NowLine, workingEditor, &Editor::SLOT_ChangeLineNum);

    filePath = filepath;
    fileName = filename;

    Write(filePath.left(2));
    Write("cd "+filePath);
    Write("g++ -g "+fileName+" -o main");
    Write("gdb main");
    Write("set new-console on");

    QVector<qint32>::iterator iter;
    QVector<qint32> breakPoints = workingEditor->GetBreakPoints();
    for (iter=breakPoints.begin();iter!=breakPoints.end();iter++)
    {
        Write("break "+ QString::number(*iter));
    }

    LogWrite("run");
}
