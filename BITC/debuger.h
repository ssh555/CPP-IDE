#ifndef DEBUGER_H
#define DEBUGER_H

#include <QWidget>
#include <QProcess>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class Debuger; }
QT_END_NAMESPACE

class Debuger : public QWidget
{
    Q_OBJECT

public:
    Debuger(QWidget *parent, QString filename, QString filepath, QVector<qint32> breakpoints);
    ~Debuger();
    void SetBreakPoints(QVector<qint32> breakpoints);
    void SetFile(QString file);
    void ReadyToStart();
    void SetFilePath(QString Filepath);

public slots:
    void Read();
    void ReadLog();

private:
    QProcess *debuger;
    QFile *logFile;
    QTextStream *logStream;
    QVector<qint32> breakPoints;
    QString filePath, fileName;
    QRegExp lineNumber, variable;
    void Write(QString command);
    void LogWrite(QString command);
    int GetNowLine();
    void SetBreak();

signals:
    void CommandFinished();
    void SIGNAL_NowLine(int lineNumber);

private:
    Ui::Debuger *ui;
};
#endif // DEBUGER_H
