#ifndef UIINTERFACE_H
#define UIINTERFACE_H

#include <QObject>
#include <QMenuBar>
#include <QTabWidget>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>

#include <mainwindow.h>

class UIInterface : public QObject
{
    Q_OBJECT
public:

    static UIInterface* Instance()
    {
        if (m_pInstance == NULL)
        {
            m_pInstance = new UIInterface();
        }
        return m_pInstance;
    }
    //总的编辑区的TABWIDHET
    QTabWidget* tabEditArea = MainWindow::Instance()->GettabWgtEditArea();


private:
    explicit UIInterface(QObject *parent = nullptr);
    static UIInterface* m_pInstance;

    //总窗口MainWidget
    MainWindow* mainWindow = MainWindow::Instance();

    //总的结果区
    QTabWidget* tabResArea = MainWindow::Instance()->GettabWgtResArea();
    //总的资源管理器
    QDockWidget* gBoxFileMgr = MainWindow::Instance()->GetgBoxFileMgr();
    //总的菜单栏
    QMenuBar* menuBar = MainWindow::Instance()->Getmenubar();
    //总的工具栏
    QToolBar* toolBar = MainWindow::Instance()->GettoolBar();
    //下方提示栏
    QStatusBar* statusBarTips = MainWindow::Instance()->GetstatusbarTips();

    //更改总窗口，下方的函数可在此函数中调用，即只调用这一个函数即可完成风格更改
    void SetUIInteface();

    //更改 总的tabEditArear
    void SetTabEditArea();
    //更改 总的tabResArear
    void SetTabResArea();
    //更改 总的menuBar
    void SetMenuBar();
    //更改 总的gBoxFileMgr
    void SetGBoxFileMgr();
    //更改 总的toolBar
    void SetToolBar();
    //更改 提示栏
    void SetStatusBarTips();

signals:

public slots:
    void SLOT_ChangeCodeFont(bool flag);
};

#endif // UIINTERFACE_H
