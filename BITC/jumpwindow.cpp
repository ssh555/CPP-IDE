#include "jumpwindow.h"
#include "ui_jumpwindow.h"

JumpWindow::JumpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JumpWindow)
{
    ui->setupUi(this);

}
void JumpWindow::Init(Editor *e){
    editor=e;
    connect(this,&JumpWindow::SIGNAL_ChangeLine,editor,&Editor::SLOT_ChangeLineNum);
    this->ui->lineEdit->setFocus();
}
void JumpWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Return){
        emit SIGNAL_ChangeLine(ui->lineEdit->text().toInt());
        this->close();
    }
}
JumpWindow::~JumpWindow()
{
    delete ui;
}
