#ifndef DEBUGER_H
#define DEBUGER_H

#include <QWidget>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include "editor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Debuger; }
QT_END_NAMESPACE

class Debuger : public QWidget
{
    Q_OBJECT

public:
    Debuger(QWidget *parent);
    ~Debuger();
//    void SetBreakPoints(QVector<qint32> breakPoints);
//    void SetFile(QString filePath, QString fileName);
    void Run(Editor *workingeditor, QString filePath, QString fileName);

public slots:
    void Read();

private:
    QProcess *debuger;
    QString filePath, fileName;
    Editor *workingEditor=nullptr;
    static QRegExp lineNumber, variable;
    QMetaObject::Connection connectionLineNumber;
    void Write(QString command);
    void LogWrite(QString command);

signals:
    void SIGNAL_NowLine(int lineNumber);
    void SIGNAL_DebugerRun();

private:
    Ui::Debuger *ui;
};
#endif // DEBUGER_H
