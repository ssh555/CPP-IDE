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

public slots:
    void Read();

private:
    QProcess *debuger;
    QVector<qint32> breakPoints;
    QString filePath, fileName;
    static QRegExp lineNumber, variable;
    void Write(QString command);
    void LogWrite(QString command);

signals:
    void SIGNAL_NowLine(int lineNumber);

private:
    Ui::Debuger *ui;
};
#endif // DEBUGER_H
