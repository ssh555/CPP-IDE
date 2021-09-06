#include "settingwindow.h"
#include "ui_settingwindow.h"
#include "config.h"
#include "uiinterface.h"
SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::on_CommitBtn_clicked()
{
    int num=ui->SytleBox->currentIndex()+1;
    qDebug()<<num;
    Config::GetInstance()->ChangeCodeStyle(num);
    QTabWidget* tabEditArea=UIInterface::Instance()->tabEditArea;
    num=tabEditArea->count();
    for(int i=0;i<num;i++){
        Editor *e=(Editor*)tabEditArea->widget(i);
        e->ChangeCodeStyle();
    }
    this->close();
}
