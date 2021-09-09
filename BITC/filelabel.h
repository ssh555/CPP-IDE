#ifndef FILELABEL_H
#define FILELABEL_H

#include <QLabel>
#include <QEvent>

class FileLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FileLabel(QWidget *parent = nullptr);
    FileLabel(QString filename, QWidget *parent = nullptr);

    void SetFilePath(QString path);

protected:

    void mousePressEvent(QMouseEvent *ev) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;

private:
    void Init();//初始化文本框
    QString filePath;//对应的文件完整路径


signals:

};

#endif // FILELABEL_H
