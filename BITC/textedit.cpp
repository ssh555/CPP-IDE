#include "textedit.h"

#include <qtextedit.h>

TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent)
{

}
TextEdit::TextEdit(QWidget *parent,QString foldername) : QTextEdit(parent){
    FolderName = foldername;
}
