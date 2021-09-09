#include "settingwindow.h"
#include "ui_settingwindow.h"
#include "config.h"
#include "uiinterface.h"

#include <QThread>
#include <QtConcurrent>

SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    this->Init();
}
void SettingWindow::Init()
{
    //初始化setting
    setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    //初始化字体组
    QFontDatabase database;
    foreach(const QString &family, database.families())
    {
        ui->comboBox_5->addItem(family);
    }
    //初始化combobox,让它们指向默认选项
    ui->comboBox_5->setCurrentText(setting->value("CodeFont").toString());
    ui->comboBox->setCurrentText(setting->value("editorfontsize").toString());
    ui->SytleBox->setCurrentIndex(setting->value("styleflag").toUInt()-1);
    ui->comboBox_4->setCurrentIndex(!(setting->value("autosave").toUInt()));

}
SettingWindow::~SettingWindow()
{
    delete ui;
}
//提交
void SettingWindow::on_CommitBtn_clicked()
{
    //num现在是记录选择的代码风格()
    int num=ui->SytleBox->currentIndex()+1;
    Config::GetInstance()->ChangeCodeStyle(num);
    MainWindow::isReadingOrWriting = true;
    QFuture<void> ftr = QtConcurrent::run(inf,&UIInterface::ChangeCodeStyle);
    while(ftr.isRunning())
        continue;
    //ftr.waitForFinished();
    MainWindow::isReadingOrWriting = false;
    //inf->ChangeCodeStyle();

    //字体设置
    QString fontfamily=ui->comboBox_5->currentText();
    setting->setValue("CodeFont",fontfamily);
    //现在num成为了字体大小
    num=(ui->comboBox->currentText()).toUInt();
    inf->ChangeCodeFont(num);
    //自动保存设置 是->自动保存(0位置)
    MainWindow::Instance()->SetAutoSave(ui->comboBox_4->currentIndex()==0);
    setting->setValue("autosave",ui->comboBox_4->currentIndex()==0);
    this->close();
}

void SettingWindow::on_pushButton_clicked()
{
    this->close();
}
