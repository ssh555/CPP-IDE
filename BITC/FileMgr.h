#ifndef FILEMGR_H
#define FILEMGR_H

#include <QWidget>
#include "toolboxchild.h"

namespace Ui {
class FileMgr;
}

class FileMgr : public QWidget
{
    Q_OBJECT

public:
    explicit FileMgr(QWidget *parent = nullptr);
    ~FileMgr();

    //添加文件夹下的文件
    void AddFileLabel(QString filename);
    //添加文件夹
    void AddFolderLabel(QString foldername);
    //添加文件夹下的文件夹

private:
    Ui::FileMgr *ui;

    ToolBoxChild *tBoxFolderChild;

    //存储已打开的文件夹
    static QStringList *openedFolders;
};

#endif // FILEMGR_H
