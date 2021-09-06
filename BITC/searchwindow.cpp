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

//    this->setStyleSheet("border: 20px lightGray;");
    //让窗口其他部件消失
    setWindowFlags(Qt::FramelessWindowHint);
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
        disconnect(this,&SearchWindow::SIGNAL_FindNext,editor_far,&Editor::SLOT_FindKeywords);
        disconnect(this,&SearchWindow::SIGNAL_FindWhole,editor_far,&Editor::SLOT_FindWhole);
        disconnect(this,&SearchWindow::SIGNAL_FindPrivious,editor_far,&Editor::SLOT_FindPrivious);
        disconnect(this,&SearchWindow::SIGNAL_ReplaceNext,editor_far,&Editor::SLOT_ReplaceKeywords);
        disconnect(this,&SearchWindow::SIGNAL_ReplaceWhole,editor_far,&Editor::SLOT_ReplaceWhole);
        disconnect(this,&SearchWindow::SIGNAL_ReplacePrivious,editor_far,&Editor::SLOT_ReplacePrivious);
        disconnect(this,&SearchWindow::SIGNAL_Exit,editor_far,&Editor::SLOT_SearchEnd);
        disconnect(ui->btnReplace,&QPushButton::clicked,editor_far,&Editor::SLOT_SearchEnd);
    }
    this->editor=editor_far;
    //connect(this,&SearchWindow::on_btnFindNext_clicked,this,&SearchWindow::BtnFindNextClicked);//this->editor,&Editor::SLOT_FindKeywords
    connect(this,&SearchWindow::SIGNAL_FindNext,editor_far,&Editor::SLOT_FindKeywords);
    connect(this,&SearchWindow::SIGNAL_FindWhole,editor_far,&Editor::SLOT_FindWhole);
    connect(this,&SearchWindow::SIGNAL_FindPrivious,editor_far,&Editor::SLOT_FindPrivious);
    connect(this,&SearchWindow::SIGNAL_ReplaceNext,editor_far,&Editor::SLOT_ReplaceKeywords);
    connect(this,&SearchWindow::SIGNAL_ReplaceWhole,editor_far,&Editor::SLOT_ReplaceWhole);
    connect(this,&SearchWindow::SIGNAL_ReplacePrivious,editor_far,&Editor::SLOT_ReplacePrivious);
    connect(this,&SearchWindow::SIGNAL_Exit,editor_far,&Editor::SLOT_SearchEnd);
    connect(ui->btnReplace,&QPushButton::clicked,editor_far,&Editor::SLOT_SearchEnd);
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

void SearchWindow::on_btnCancel_clicked()//关掉,统统关掉
{
    emit(SIGNAL_Exit());
    this->close();
}


//获取鼠标的按下操作
//用于移动
void SearchWindow::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() ==Qt::LeftButton)
    this->posMouseOrigin = QCursor::pos(); //cursor是一个光标类；
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
//获得鼠标移动的操作
void SearchWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() &Qt::LeftButton){
        QPoint ptMouseNow = QCursor::pos();
        QPoint ptDelta = ptMouseNow - this->posMouseOrigin;
        move(this->pos() + ptDelta); posMouseOrigin = ptMouseNow;
    }
}

