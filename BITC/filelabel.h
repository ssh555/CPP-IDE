#ifndef FILELABEL_H
#define FILELABEL_H

#include <QLabel>

class FileLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FileLabel(QWidget *parent = nullptr);
    FileLabel(QString title, QWidget *parent = nullptr);

private:
    void Init();//初始化文本框
    QString fileName;//对应的文件完整路径

signals:

};

#endif // FILELABEL_H
