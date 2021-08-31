#include "filelabel.h"

#include <QLabel>
#include <QFileInfo>

FileLabel::FileLabel(QWidget *parent) : QLabel(parent)
{
    Init();
}
FileLabel::FileLabel(QString title, QWidget *parent) : QLabel(QFileInfo(title).fileName(),parent)
{
    fileName = title;
    Init();
}

void FileLabel::Init(){
    this->setMargin(1);
    this->setIndent(16);
}
