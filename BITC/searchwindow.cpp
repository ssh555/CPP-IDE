#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QLineEdit>
#include "mainwindow.h"
#include <QMouseEvent>
SearchWindow::SearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    //移动到该去的地方
    this->move(200,0);
    ui->horizontalLayout_2->addStretch();
    ui->horizontalLayout_2->setSpacing(0);

//    this->setStyleSheet("border: 20px lightGray;");
    //让窗口其他部件消失
    QSettings *setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());

    QString fontname=setting->value("CodeFont").toString();
    setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit->setStyleSheet("QLineEdit {"
                               " border: 1px solid rgb(41, 57, 85);"
                               " border-radius: 3px; "
                               " background: white; "
                               " selection-background-color: green; "
                               " font-size: 14px ;"
                            "}"

                           " QLineEdit:hover {"
                               " border: 1px solid blue;"
                            "}");

    //连接槽函数
    connect(ui->btnFindWhole,&QPushButton::clicked,this,&SearchWindow::on_btnFindWhole_clicked);
    connect(ui->btnFindPrivious,&QPushButton::clicked,this,&SearchWindow::on_btnFindPrivious_clicked);
    connect(ui->btnReplace,&QPushButton::clicked,this,&SearchWindow::on_btnReplace_clicked);
    connect(ui->btnFind,&QPushButton::clicked,this,&SearchWindow::on_btnFind_clicked);

}
SearchWindow::~SearchWindow()
{
    delete ui;
    this->destroy();
}
void SearchWindow::Focus(){
    this->ui->lineEdit->setFocus();
}
void SearchWindow::on_btnFind_clicked()
{
    if(this->mode==1){//mode1:替换
        //修改ui
        ui->btnFindWhole->setText("查找全文");
        ui->btnFindPrivious->setText("上一个");
        ui->btnFindNext->setText("下一个");
        delete(replacelayoutH);
        delete(replacelayoutV);
        delete(replaceLabel);
        delete(ReplaceLineEdit);

        this->mode=0;//replace mode
    }
}
void SearchWindow::on_btnReplace_clicked()
{
    if(this->mode==0){//mode0:查找
        //修改ui
        ui->btnFindWhole->setText("替换全部");
        ui->btnFindPrivious->setText("替换前一个");
        ui->btnFindNext->setText("替换下一个");
        replacelayoutV=new QVBoxLayout();
        ui->verticalLayout->addLayout(replacelayoutV);
        replacelayoutH=new QHBoxLayout();
        replacelayoutV->addLayout(replacelayoutH);
        replaceLabel=new QLabel();
        replacelayoutH->addWidget(replaceLabel);

        replaceLabel->setText("替换为");
        this->ReplaceLineEdit=new QLineEdit();
        replacelayoutH->addWidget(ReplaceLineEdit);

        this->mode=1;//replace mode
    }
}
void SearchWindow::setEditor(Editor *editor_far)//设置editor,连接槽函数
{
    if(this->editor!=NULL){

//        disconnect(this,&SearchWindow::SIGNAL_FindNext,editor_far,&Editor::SLOT_FindKeywords);
//        disconnect(this,&SearchWindow::SIGNAL_FindWhole,editor_far,&Editor::SLOT_FindWhole);
//        disconnect(this,&SearchWindow::SIGNAL_FindPrivious,editor_far,&Editor::findPrivious);
//        disconnect(this,&SearchWindow::SIGNAL_ReplaceNext,editor_far,&Editor::SLOT_ReplaceKeywords);
//        disconnect(this,&SearchWindow::SIGNAL_ReplaceWhole,editor_far,&Editor::SLOT_ReplaceWhole);
//        disconnect(this,&SearchWindow::SIGNAL_ReplacePrivious,editor_far,&Editor::SLOT_ReplacePrivious);
//        disconnect(ui->btnReplace,&QPushButton::clicked,editor_far,&Editor::SLOT_SearchEnd);
        disconnect(connect1);
        disconnect(connect2);
        disconnect(connect3);
        disconnect(connect4);
        disconnect(connect5);
        disconnect(connect6);
        disconnect(connect7);
        //qDebug()<<"notnull";
    }
    this->editor=editor_far;
    //connect(this,&SearchWindow::on_btnFindNext_clicked,this,&SearchWindow::BtnFindNextClicked);//this->editor,&Editor::SLOT_FindKeywords
    connect1=connect(this,&SearchWindow::SIGNAL_FindNext,editor_far,&Editor::SLOT_FindKeywords);
    connect2=connect(this,&SearchWindow::SIGNAL_FindWhole,editor_far,&Editor::SLOT_FindWhole);
    connect3=connect(this,&SearchWindow::SIGNAL_FindPrivious,editor_far,&Editor::findPrivious);
    connect4=connect(this,&SearchWindow::SIGNAL_ReplaceNext,editor_far,&Editor::SLOT_ReplaceKeywords);
    connect5=connect(this,&SearchWindow::SIGNAL_ReplaceWhole,editor_far,&Editor::SLOT_ReplaceWhole);
    connect6=connect(this,&SearchWindow::SIGNAL_ReplacePrivious,editor_far,&Editor::SLOT_ReplacePrivious);
    connect7=connect(ui->btnReplace,&QPushButton::clicked,editor_far,&Editor::SLOT_SearchEnd);

}
void SearchWindow::on_btnFindWhole_clicked()//找所有的
{
    searchtext=ui->lineEdit->text();
    if (mode==0){//查找
        emit(SIGNAL_FindWhole(searchtext));
    }else if(mode==1){//替换
        emit(SIGNAL_ReplaceWhole(searchtext,ReplaceLineEdit->text()));
    }

}
void SearchWindow::on_btnFindPrivious_clicked()//找上一个
{
    searchtext=ui->lineEdit->text();
    if(mode==0){
        emit(SIGNAL_FindPrivious(searchtext));
    }else if(mode==1){
        emit(SIGNAL_ReplacePrivious(searchtext,ReplaceLineEdit->text()));
    }

}
void SearchWindow::on_btnFindNext_clicked()//找下一个
{
    searchtext=ui->lineEdit->text();
    if(mode==0){
        emit(SIGNAL_FindNext(searchtext));
    }else if(mode ==1){
        emit(SIGNAL_ReplaceNext(searchtext,ReplaceLineEdit->text()));
    }

}




//回车查找下一个
void SearchWindow::keyPressEvent(QKeyEvent *event)
{
    searchtext=ui->lineEdit->text();

    if( event ->key() == Qt::Key_Enter){
        emit SIGNAL_FindNext(searchtext);
    }

}
void SearchWindow::showWithText(QString text)
{
    this->ui->lineEdit->setText(text);

    ui->lineEdit->setFocus();
    this->show();
}


