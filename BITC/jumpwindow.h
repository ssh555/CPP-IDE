#ifndef JUMPWINDOW_H
#define JUMPWINDOW_H

#include <QWidget>
#include "editor.h"
namespace Ui {
class JumpWindow;
}

class JumpWindow : public QWidget
{
    Q_OBJECT

public:
    explicit JumpWindow(QWidget *parent = nullptr);
    ~JumpWindow();
    Editor *editor;
    void Init(Editor *e);
signals:
    void SIGNAL_ChangeLine(int num);
private:
    Ui::JumpWindow *ui;
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // JUMPWINDOW_H
