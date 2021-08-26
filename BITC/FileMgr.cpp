#include "FileMgr.h"
#include "ui_FileMgr.h"

FileMgr::FileMgr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileMgr)
{
    ui->setupUi(this);
}

FileMgr::~FileMgr()
{
    delete ui;
}
