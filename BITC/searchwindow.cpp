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
    setWindowFlags(Qt::FramelessWindowHint);

    //
//    connect(this,&SearchWindow::BtnFindNextClicked,);
}//
SearchWindow::~SearchWindow()
{
    delete ui;
}
void SearchWindow::setEditor(Editor *editor_far)
{
    this->editor=editor_far;
    //connect(this,&SearchWindow::on_btnFindNext_clicked,this,&SearchWindow::BtnFindNextClicked);//this->editor,&Editor::SLOT_FindKeywords

}
void SearchWindow::on_btnFindNext_clicked()
{
    searchtext=ui->lineEdit->text();
    emit(BtnFindNextClicked(searchtext));
}

void SearchWindow::on_btnCancel_clicked()
{
    this->close();
}

void SearchWindow::on_btnExit_clicked()
{
    this->close();
}
//获取鼠标的按下操作
void SearchWindow::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() ==Qt::LeftButton)
    this->posMouseOrigin = QCursor::pos(); //cursor是一个光标类；
}
void SearchWindow::keyPressEvent(QKeyEvent *event)
{
    searchtext=ui->lineEdit->text();
    emit(BtnFindNextClicked(searchtext));
    if( event ->key() == Qt::Key_Enter){
        emit BtnFindNextClicked(searchtext);
    }
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

