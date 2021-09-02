#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>
#include "editor.h"
namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
    Q_OBJECT

public:
    void setEditor(Editor *editor_far);
    Editor *editor;
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();
    QString searchtext;//查询语句
    //移动窗口
    void mousePressEvent(QMouseEvent *ev)override;
    void mouseMoveEvent(QMouseEvent *ev)override;
    //带参展示
    void showWithText(QString text);

    //释放窗口
    //鼠标原始位置
    void keyPressEvent(QKeyEvent *event) override;//回车查询
    QPoint posMouseOrigin;
signals:
    void BtnFindNextClicked(QString findtext);
private slots:
    void on_btnFindNext_clicked();

    void on_btnCancel_clicked();

    void on_btnExit_clicked();

private:
    Ui::SearchWindow *ui;
};

#endif // SEARCHWINDOW_H
