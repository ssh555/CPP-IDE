#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>
#include "editor.h"
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
    Q_OBJECT

public:

    void setEditor(Editor *editor_far);
    QLineEdit *ReplaceLineEdit=NULL;
    QLabel *replaceLabel=NULL;
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
    QHBoxLayout *replacelayoutH=NULL;
    QVBoxLayout *replacelayoutV=NULL;
    void on_btnReplace_clicked();
signals:
    void SIGNAL_FindNext(QString findtext);
    void SIGNAL_FindPrivious(QString findtext);
    void SIGNAL_FindWhole(QString findtext);
    void SIGNAL_ReplaceNext(QString findtext,QString replacetext);
    void SIGNAL_ReplacePrivious(QString findtext,QString replacetext);
    void SIGNAL_ReplaceWhole(QString findtext,QString replacetext);
    void SIGNAL_Exit();
private slots:
    void on_btnFindNext_clicked();

    void on_btnCancel_clicked();

    void on_btnFindWhole_clicked();

    void on_btnFindPrivious_clicked();



    void on_btnFind_clicked();
private:
    int mode=0;//0--find,1--replace
    Ui::SearchWindow *ui;
};

#endif // SEARCHWINDOW_H
