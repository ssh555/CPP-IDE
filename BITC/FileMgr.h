#ifndef FILEMGR_H
#define FILEMGR_H

#include <QWidget>
#include "toolboxchild.h"
#include <QFileSystemWatcher>

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

    //存储已打开的文件夹
    static QStringList *openedFolders;

    //更新文件夹
    void UpdateFolder();

private:
    Ui::FileMgr *ui;

    ToolBoxChild *tBoxFolderChild;

    //保存当前FileMgr所打开的文件
    QString folderName;

    QFileSystemWatcher * watch;


};

#endif // FILEMGR_H
