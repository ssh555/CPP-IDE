#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QObject>
#include <qtextedit.h>


class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = nullptr);
    TextEdit(QWidget *parent,QString foldername);
    QString FolderName;//保存当前页的文件的文件夹绝对路径

signals:

};

#endif // TEXTEDIT_H
