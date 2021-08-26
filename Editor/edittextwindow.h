#ifndef EDITTEXTWINDOW_H
#define EDITTEXTWINDOW_H

#include <QMainWindow>
#include "ui_edittextwindow.h"
#include "editor.h"
#include "highlighter.h"
#include "type.h"
class EditTextWindow : public QMainWindow,Ui::EditTextWindow
{
    Q_OBJECT

public:
    QString file_path;
    explicit EditTextWindow(QWidget *parent = 0);
    ~EditTextWindow();

private:
     Editor *configEditor;
};

#endif // EDITTEXTWINDOW_H
