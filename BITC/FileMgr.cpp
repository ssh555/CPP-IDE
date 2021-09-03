#include "FileMgr.h"
#include "ui_FileMgr.h"

#include <filelabel.h>
#include <QVBoxLayout>

#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QFileSystemWatcher>

#include "toolboxchild.h"

FileMgr::FileMgr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileMgr)
{
    ui->setupUi(this);

    tBoxFolderChild = new ToolBoxChild(this);
    ui->verticalLayout->addWidget(tBoxFolderChild);

}

FileMgr::~FileMgr()
{
    delete ui;
}

void FileMgr::AddFileLabel(QString filename){
    ui->verticalLayout->addWidget(new FileLabel(filename,this));
}
void FileMgr::AddFolderLabel(QString foldername){
    folderName = foldername;
    if(openedFolders->contains(folderName))
        return;
    openedFolders->append(folderName);
    QDir dir(foldername);
    QStringList allFilesNames = dir.entryList();
    for(int i = 2; i < allFilesNames.size(); ++i){
        QString str = foldername + "/" + allFilesNames.at(i);
        if(QFileInfo(str).isDir()){
            FileMgr *fileMgr = new FileMgr(this);
            ui->verticalLayout->addWidget(fileMgr);
            fileMgr->AddFolderLabel(str);
            tBoxFolderChild->addWidget(QFileInfo(str).fileName(), fileMgr);
            //AddFileLabel(str);
        }
        else{
            AddFileLabel(str);
        }
    }

    watch = new QFileSystemWatcher(this);
    connect(watch, &QFileSystemWatcher::directoryChanged, [=](){

        UpdateFolder();
    });
    watch->addPath(folderName);
}

void FileMgr::UpdateFolder(){
    qDebug() << folderName;
    //清空布局内的所有元素
    QLayoutItem *child;
    while ((child = ui->verticalLayout->takeAt(0)) != 0)
    {
        //setParent为NULL，防止删除之后界面不消失
        //ui->verticalLayout->removeItem(child);
        child->widget()->deleteLater();
        //ui->verticalLayout->removeWidget(child->widget());
        delete child;
    }
    delete tBoxFolderChild;
    tBoxFolderChild = new ToolBoxChild(this);
    ui->verticalLayout->addWidget(tBoxFolderChild);
    QDir dir(folderName);
    QStringList allFilesNames = dir.entryList();
    for(int i = 2; i < allFilesNames.size(); ++i){
        QString str = folderName + "/" + allFilesNames.at(i);
        if(QFileInfo(str).isDir()){
            FileMgr *fileMgr = new FileMgr(this);
            ui->verticalLayout->addWidget(fileMgr);
            fileMgr->AddFolderLabel(str);
            tBoxFolderChild->addWidget(QFileInfo(str).fileName(), fileMgr);
            //AddFileLabel(str);
        }
        else{
            AddFileLabel(str);
        }
    }
}

QStringList *FileMgr::openedFolders = new QStringList;
