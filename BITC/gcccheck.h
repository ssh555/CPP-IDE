#ifndef GCCCHECK_H
#define GCCCHECK_H
#include<QObject>
#include<QProcess>
#include<QWidget>
class gccCheck : public QWidget
{
    Q_OBJECT

public:
    gccCheck(QWidget *parent=nullptr);
    void gccCheckAndInstall();
private:
    QString cmdoutput;
    QString str;
};

#endif // GCCCHECK_H

