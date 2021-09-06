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
//有大量无用代码，函数不一定有用

Debuger::Debuger(QWidget *parent, QString filename, QString filepath, QVector<qint32> breakPoints)
    : QWidget(parent)
    , ui(new Ui::Debuger)
{
    ui->setupUi(this);
    fileName = filename;
    filePath = filepath;

    lineNumber = QRegExp("^#.* at .*:.*");
    variable = QRegExp("[0-9]{1,4}: .* = .*");

    logFile = new QFile(filePath+"/gdb.txt");
    logFile->open(QIODevice::ReadOnly);
    logStream = new QTextStream(logFile);

#pragma region "Buttons" {

    connect(ui->Start, &QPushButton::clicked, this, [=]{
        Write("run");
    });

    connect(ui->Stop, &QPushButton::clicked, this, [=]{
        Write("q");
        Write("y");
        close();
    });

    connect(ui->StepInto, &QPushButton::clicked, this, [=]{
        LogWrite("step");
//        ui->BreakView->append(QString::number(GetNowLine()));
    });

    connect(ui->StepOut, &QPushButton::clicked, this, [=]{
        LogWrite("finish");
//        ui->BreakView->append(QString::number(GetNowLine()));
    });

    connect(ui->StepOver, &QPushButton::clicked, this, [=]{
        LogWrite("next");
//        ui->BreakView->append(QString::number(GetNowLine()));
    });

    connect(ui->Continue, &QPushButton::clicked, this, [=]{
        LogWrite("continue");
//        ui->BreakView->append(QString::number(GetNowLine()));
    });

    connect(ui->DisplayButton, &QPushButton::clicked, this, [=]{
        Write("display "+ui->DisplayLine->text());
        ui->DisplayLine->clear();
    });

    connect(ui->BreakButton, &QPushButton::clicked, this, [=]{
        Write("break "+ui->BreakLine->text());
        ui->BreakLine->clear();
    });

    connect(ui->EnterButton, &QPushButton::clicked, this, [=]{
        Write(ui->EnterLine->text());
        ui->EnterLine->clear();
    });
#pragma endregion}


    debuger = new QProcess();
    debuger->start("cmd.exe");
    connect(debuger, &QProcess::readyRead, this, &Debuger::Read);

    Write(filePath.left(2));
    Write("cd "+filePath);
    Write("gcc -g "+fileName+" -o main");
    Write("gdb main");
    Write("set logging overwrite on");

    //SetBreakPoints
    qint32 b = 0;
    foreach(b, breakPoints);
    {
        Write("break "+QString::number(b));
    }

    Write("run");
}

Debuger::~Debuger()
{
    delete ui;
    delete debuger;
    logFile->close();
    delete logFile;
    delete logStream;

}
void Debuger::ReadyToStart(){

}




void Debuger::Write(QString command)
{
//    qDebug()<<command;
    command+="\r\n";
    debuger->write(command.toLatin1().data(), command.length());
}

void Debuger::LogWrite(QString command)
{

//    Write("set logging on");
    Write(command);
//    Write("set logging off");
//    debuger->waitForFinished(100);
//    qDebug()<<"readReady";
//    Write("set logging on");
    Write("frame");
//    QString log = QString::fromLocal8Bit(logFile->readLine());
//    qDebug()<<log;
//    ReadLog();
}

void Debuger::Read()
{
    QString log  = QString::fromLocal8Bit(debuger->readAll());
    log.replace("(gdb) ","");
    QStringList tempList = log.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    foreach(QString string, tempList) {
        int temp = -1;

        //判断是否含有行号字符串
        temp = lineNumber.indexIn(string);
        if(temp>=0) {
            int number = string.mid(string.lastIndexOf(':')+1).replace("\r\n", "").toInt();
            ui->NowLineNumber->setText(QString::number(number));
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
                qDebug()<<ui->DisplayView->rowCount();
            }
            ui->DisplayView->setItem(id-1, 0, new QTableWidgetItem(name));
            ui->DisplayView->setItem(id-1, 1, new QTableWidgetItem(value));
        }
    }
    ui->Information->append(log);
    ui->Information->update();
}

void Debuger::ReadLog()
{
    QString log = QString::fromLocal8Bit(logFile->readAll());
    log.replace("(gdb) ", "");
    QStringList tempList = log.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    if(tempList.isEmpty()){
//        qDebug()<<"empty";
        return;
    }
    foreach(QString string, tempList) {
        if(QRegExp("^[0-9]").indexIn(string, 0)>=0) {
            if(QRegExp(".*: .* = .*").indexIn(string, 0)>=0)
            {
//                qDebug()<<string<<" .*: .* = .*";
//                ui->DisplayView->append(string);
            }
//            else {
//                qDebug()<<string<<" ^[0-9]";
//                ui->BreakView->append(string);
//            }
        }
//        else
//            qDebug()<<string<<"  false";
    }
}

int Debuger::GetNowLine()
{
    LogWrite("frame");
    QString log = QString::fromLocal8Bit(logFile->readLine());

    if(log.isEmpty()){
//        qDebug()<<"empty";
        return -1;
    }
    int number = log.mid(log.lastIndexOf(':')+1).replace("\r\n", "").toInt();
//    ui->BreakView->append(QString::number(number));
    emit SIGNAL_NowLine(number);
    return number;
}

void Debuger::SetBreak()
{

}

void Debuger::SetBreakPoints(QVector<qint32> breakpoints)
{
    breakPoints = breakpoints;
}

void Debuger::SetFilePath(QString file)
{
    filePath = file;
}
void Debuger::SetFile(QString file)
{
    fileName=file;
}
