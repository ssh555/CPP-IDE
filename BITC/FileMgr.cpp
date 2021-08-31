#include "FileMgr.h"
#include "ui_FileMgr.h"

#include <filelabel.h>
#include <QVBoxLayout>

#include <QFileInfo>
#include <QDir>
#include <QDebug>

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
    QDir dir(foldername);
    QStringList allFilesNames = dir.entryList();
    for(int i = 2; i < allFilesNames.size(); ++i){
        QString str = foldername + "/" + allFilesNames.at(i);
        if(QFileInfo(str).isDir()){
            FileMgr *fileMgr = new FileMgr(this);
            fileMgr->AddFolderLabel(str);
            ui->verticalLayout->addWidget(fileMgr);
            tBoxFolderChild->addWidget(QFileInfo(str).fileName(), fileMgr);
            //AddFileLabel(str);
        }
        else{
            AddFileLabel(str);
        }
    }

}

QStringList *FileMgr::openedFolders = new QStringList;
